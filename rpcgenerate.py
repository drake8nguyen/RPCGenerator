# !/bin/env python
#
#          print signatures of all the functions named in supplied IDL file
#

import subprocess
import json
import sys
import os
from collections import defaultdict
IDL_TO_JSON_EXECUTABLE = './idl_to_json'

struct_attributes = defaultdict(list)

# Write all header and library include
def write_dependency(proxy_file, filename, is_prox):
    if is_prox:
        proxy_file.write("#include \"rpcproxyhelper.h\"\n")
    else:
        proxy_file.write("#include \"rpcstubhelper.h\"\n")
    proxy_file.write("#include <cstdio>\n")
    proxy_file.write("#include <cstring>\n")
    proxy_file.write("#include \"c150debug.h\"\n")
    proxy_file.write("#include \"c150grading.h\"\n")
    proxy_file.write("using namespace std;\n")
    proxy_file.write("#include \"" + filename + "\"" "\n")
    proxy_file.write("using namespace C150NETWORK;\n")
    proxy_file.write("void extractFromStream(char *buffer, unsigned int bufSize);\n\n")

# The part that call the actual function
def write_stub_function(stub_file, rtype, func_name, argstring, argstring2):
    stub_file.write(rtype + " __" + func_name + "(" + argstring + ") {" + "\n") 
    stub_file.write("\tchar doneBuffer[] = \"DONE\";\n") 
    stub_file.write("\t*GRADING << \"Invoking: "+func_name+"()\" << endl;\n")
    stub_file.write("\t"+rtype+" result = "+func_name+"(" + argstring2 + ");\n")

# send done message at the end of each stub function
def write_send_done(stub_file):
    stub_file.write("\t*GRADING << \"Return from function -- responding to client\" << endl;\n")
    stub_file.write("\tRPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);\n")
    stub_file.write("\treturn result;\n}\n")

# dispatch function in stub
def write_dispatch(stub_file, args, functions):
    stub_file.write("void __badFunction(const char *functionName) {\n")
    stub_file.write("\tchar doneBuffer[5] = \"BAD\";\n")
    stub_file.write("\t*GRADING << \"received call for nonexistent function \" << functionName << \"()\" << endl;\n")
    stub_file.write("\tRPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);\n}\n")
    stub_file.write("void dispatchFunction() {\n")
    stub_file.write("\tchar functionNameBuffer[50];\n")
    stub_file.write("\textractFromStream(functionNameBuffer,sizeof(functionNameBuffer));\n")
    stub_file.write("\tif (!RPCSTUBSOCKET-> eof()) {\n")

    for name, sig in functions.iteritems():
        stub_file.write("\t\tif (strcmp(functionNameBuffer,\""+name+"\") == 0) {\n")
        args = sig["arguments"]
        for a in args:
            write_recv(stub_file, a["type"], a["name"], 0, struct_attributes[a["type"]], '')
        argstrings = generate_argstring(args)
        stub_file.write("\t\t\t__"+name+"("+argstrings[1]+");\n\t\t} else\n")
    stub_file.write("\t\t\t__badFunction(functionNameBuffer);\n\t\t}\n}\n\n")

# start of each proxy function, send function name
def write_send_function_name(proxy_file, rtype, func_name, args):
    proxy_file.write(rtype + " " + func_name + "(" + args + ") {" + "\n") 
    proxy_file.write("\tchar readBuffer[5];\n") #buffer for DONE message
    proxy_file.write("\tRPCPROXYSOCKET->write(\"" + func_name + \
        "\", strlen(\""+ func_name + "\")+1);\n") # write function name to server


def write_send(proxy_file, type, name, layer, members, loop_var, is_prox):
    if type == "string" or type == "__string":
        if loop_var:
            write_send_string(proxy_file, name+'['+loop_var+']', layer, is_prox)
        else:
            write_send_string(proxy_file, name, layer, is_prox)
    elif type == "float" or type == "int" or type == "__float" or type == "__int":
        if loop_var: # check if inside for loop
            write_send_num(proxy_file, name+'['+loop_var+']', layer, is_prox)
        else: 
            write_send_num(proxy_file, name, layer, is_prox)
    elif '[' in type: # if type is array
        if loop_var:
            write_send_array(proxy_file, type, name+'['+loop_var+']', layer, is_prox)
        else:
            write_send_array(proxy_file, type, name, layer, is_prox)
    else: # type is struct
        if loop_var:
            write_send_struct(proxy_file, type, name+'['+loop_var+']', layer, members, is_prox)
        else:
            write_send_struct(proxy_file, type, name, layer, members, is_prox)

def write_send_struct(proxy_file, type, name, layer, members, is_prox):
    # write each attribute of struct
    for mem in members:
        write_send(proxy_file, mem['type'], name[name.find('&')+1:] +'.'+mem['name'], layer, struct_attributes[mem['type']], '', is_prox)

# How to send an array
def write_send_array(proxy_file, type, name, layer, is_prox):
    loop_var = chr(layer+105) # start at 'i'
    open_brack = type.rfind("[") 
    close_brack = type.rfind("]")
    dim = type[open_brack+1:close_brack]

    proxy_file.write("\t"*(layer+1) + "for (int "+ loop_var + " = 0; " + loop_var + " < " + dim + "; " + loop_var + "++) {\n")
    write_send(proxy_file, type[:open_brack], name, layer+1, struct_attributes[type[:open_brack]], loop_var, is_prox)
    proxy_file.write("\t"*(layer+1) + "}\n\n") #close for loop


# How to send a string
def write_send_string(proxy_file, name, layer, is_prox):
    socket = "RPCPROXYSOCKET" if is_prox else "RPCSTUBSOCKET"
    proxy_file.write("\t"*(layer+1) + name + " += '\\0';\n")
    proxy_file.write("\t"*(layer+1) + socket + "->write(" + name +".c_str(), strlen("+name+".c_str())+1);\n\n")
    
# How to send a float or an int
def write_send_num(proxy_file, name, layer, is_prox):
    socket = "RPCPROXYSOCKET" if is_prox else "RPCSTUBSOCKET"
    proxy_file.write("\t"*(layer+1) + "string "+legalize(name)+" = to_string("+name+") + '\\0';\n")
    proxy_file.write("\t"*(layer+1) + socket + "->write("+legalize(name)+".c_str(), strlen("+legalize(name)+".c_str())+1);\n\n")

# Check type and call corresponding receive function
def write_recv(proxy_file, type, name, layer, members, loop_var):
    if type == "string" or type == "__string":
        if loop_var: # If it's inside a for loop, then we need to attach loop variable
            write_recv_string(proxy_file, name+'['+loop_var+']', layer)
        else:
            write_recv_string(proxy_file, name, layer)
    elif type == "int" or type == "__int":
        if loop_var:
            write_recv_num(proxy_file, name+'['+loop_var+']', layer, "stoi")
        else: 
            write_recv_num(proxy_file, name, layer, "stoi")
    elif type == "float" or type == "__float":
        if loop_var:
            write_recv_num(proxy_file, name+'['+loop_var+']', layer, "stof")
        else: 
            write_recv_num(proxy_file, name, layer, "stof")
    elif '[' in type: # if type is array
        if loop_var:
            write_recv_array(proxy_file, type, name+'['+loop_var+']', layer)
        else:
            write_recv_array(proxy_file, type, name, layer)
    else: # if type is struct
        if loop_var:
            index = ''
            for i in range(layer):
                index += '[' + chr(i+105) + ']'
            name = name[:name.find('[')]
            write_recv_struct(proxy_file, type, name+index, layer, members)
        else:
            write_recv_struct(proxy_file, type, name, layer, members)

# how to receive a struct
def write_recv_struct(proxy_file, type, name, layer, members):
    if '.' not in name:
        proxy_file.write("\t"*(layer+1) + type + " " + name + ";\n\n")
    # write each attribute of struct
    for mem in members:
        if '[' in mem['type']:
            write_recv(proxy_file, mem['type'][2:], name+"."+mem['name'], layer, struct_attributes[mem['type']], '')
        else:
            write_recv(proxy_file, mem['type'], name+"."+mem['name'], layer, struct_attributes[mem['type']], '')

# How to receive an array 
def write_recv_array(proxy_file, type, name, layer):
    loop_var = chr(layer+105) # start at 'i'
    open_brack = type.rfind("[") 
    close_brack = type.rfind("]")
    dim = type[open_brack+1:close_brack]
    proxy_file.write("\t"*(layer+1) + "for (int "+ loop_var + " = 0; " + loop_var + " < " + dim + "; " + loop_var + "++) {\n")
    write_recv(proxy_file, type[:open_brack], name, layer+1, struct_attributes[type[:open_brack]], loop_var)

    proxy_file.write("\t"*(layer+1) + "}\n\n") #close for loop

# How to receive a string
def write_recv_string(proxy_file, name, layer):
    buf_name = legalize(name)+"Buf"
    proxy_file.write("\t"*(layer+1) + "char "+buf_name+"[50];\n")
    proxy_file.write("\t"*(layer+1) + "extractFromStream("+buf_name+",sizeof("+buf_name+"));\n")
    if '.' in name: # check if it's a struct attribute
        proxy_file.write("\t"*(layer+1)+name+" = string("+buf_name+");\n\n")
    else:
        proxy_file.write("\t"*(layer+1)+"string "+name+" = string("+buf_name+");\n\n")

# How to receive an int or a float
def write_recv_num(proxy_file, name, layer, stoi_stof):
    buf_name = legalize(name)+"Buf"
    proxy_file.write("\t"*(layer+1) + "char "+buf_name+"[50];\n")
    proxy_file.write("\t"*(layer+1) + "extractFromStream("+buf_name+",sizeof("+buf_name+"));\n")
    if '.' in name: # check if it's a struct's attribute
        proxy_file.write("\t"*(layer+1)+name+" = "+stoi_stof+"("+buf_name+");\n\n") 
    else:
        proxy_file.write("\t"*(layer+1)+"int "+name+" = "+stoi_stof+"("+buf_name+");\n\n")

 # The part of the proxy that receive the done message and return result to client
def write_recv_done(proxy_file, function_name): 
    proxy_file.write("\t*GRADING << \"Invocation sent, waiting for response to "+function_name+"()\" << endl;\n")
    proxy_file.write("\tRPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE\n")
    proxy_file.write("\tif (strncmp(readBuffer,\"DONE\", sizeof(readBuffer))!=0) {\n")
    proxy_file.write("\t\tthrow C150Exception(\"funcOfStructWith2dArray.proxy: "+function_name+"() received invalid response from the server\");\n\t}\n")
    proxy_file.write("\t*GRADING << \""+function_name+"() successful return from remote call\" << endl;\n")
    proxy_file.write("\treturn result;\n}\n\n\n")

# Extract information from the TCP stream
def write_extract_from_stream(proxy_file, is_prox):
    socket = "RPCPROXYSOCKET" if is_prox else "RPCSTUBSOCKET"
    proxy_file.write("void extractFromStream(char *buffer, unsigned int bufSize) {\n")
    proxy_file.write("\tunsigned int i;\n")
    proxy_file.write("\tchar *bufp;\n")
    proxy_file.write("\tbool readnull;\n")
    proxy_file.write("\tssize_t readlen;\n")
    proxy_file.write("\treadnull = false;\n")
    proxy_file.write("\tbufp = buffer;\n")
    proxy_file.write("\tfor (i=0; i< bufSize; i++) {\n")
    proxy_file.write("\t\treadlen = "+socket+"-> read(bufp, 1);\n")
    proxy_file.write("\t\tif (readlen == 0) {\n")
    proxy_file.write("\t\t\tbreak;\n\t\t}\n")
    proxy_file.write("\t\tif (*bufp++ == '\\0') {\n")
    proxy_file.write("\t\t\treadnull = true;\n")
    proxy_file.write("\t\t\tbreak;\n\t\t}\n\t}\n")
    proxy_file.write("\tif (readlen == 0) {\n")
    proxy_file.write("\t*GRADING << \"read zero length message, checking EOF\" << endl;\n")
    proxy_file.write("\t\tif ("+socket+"-> eof()) {\n")
    proxy_file.write("\t*GRADING << \"EOF signaled on input\" << endl;\n")
    proxy_file.write("\t\t} else {\n")
    proxy_file.write("\t*GRADING << \"unexpected zero length read without eof\" << endl;\n\t\t}\n\t}\n")
    proxy_file.write("\telse if(!readnull)\n")
    proxy_file.write("\t\tthrow C150Exception(\"method name not null terminated or too long\");\n}\n")


# Remove '.' and bracket from name
def legalize(name):
    bad_chars = ['.', '[', ']']
    for i in bad_chars : 
        name = name.replace(i, '_')
    return "_"+name

def generate_argstring(args):
    arglist = [] # "(string a, int b)" for function definition
    arglist2 = [] # "(a, b)"for function call
    for a in args:
        if '[' in a["type"]:
            open_brack = a["type"].find("[") # __string[10] x, float y -> string x[10], float y)
            close_brack = a["type"].rfind("]")
            dim = a["type"][open_brack+1:close_brack]
            arglist.append(a["type"][2:open_brack] + ' ' + a["name"] + '[' + dim + ']')
            arglist2.append(a["name"])
        else:
            arglist.append(a["type"] + ' ' + a["name"])
            arglist2.append(a["name"])
    argstring = ', '.join(arglist)
    argstring2 = ', '.join(arglist2)
    return (argstring, argstring2)

def main():

    try:
        #
        #     Make sure invoked properly
        #
        if len(sys.argv) != 2:
            raise "Wrong number of arguments"

        #
        #     Make sure IDL file exists and is readable
        #
        filename = sys.argv[1]
        if (not os.path.isfile(filename)):
            print >> sys.stderr, "Path %s does not designate a file" % filename
            raise "No file named " + filename
        if (not os.access(filename, os.R_OK)):
            print >> sys.stderr, "File %s is not readable" % filename
            raise "File " + filename + " not readable"

        #
        #     Make sure idl_to_json exists and is executable
        #
        if (not os.path.isfile(IDL_TO_JSON_EXECUTABLE)):
            print >> sys.stderr,                                       \
                ("Path %s does not designate a file...run \"make\" to create it" % 
                IDL_TO_JSON_EXECUTABLE)
            raise "No file named " + IDL_TO_JSON_EXECUTABLE
        if (not os.access(IDL_TO_JSON_EXECUTABLE, os.X_OK)):
            print >> sys.stderr, ("File %s exists but is not executable" % 
                                IDL_TO_JSON_EXECUTABLE)
            raise "File " + IDL_TO_JSON_EXECUTABLE + " not executable"

        #
        #     Parse declarations into a Python dictionary
        #
        decls = json.loads(subprocess.check_output([IDL_TO_JSON_EXECUTABLE, filename]))


        # Loop printing each type signature
        for name, sig in decls["types"].iteritems():
            if sig["type_of_type"] == "struct":
                # "members" : [{"name": "firstname", "type" : "string"}, {"name" : "age", "type" : "int"}]
                struct_attributes[name] = sig["members"]
                struct_attributes["__" + name] = sig["members"] # not necessary as already handled when formatting argstring?

        pos = filename.find(".idl")
        proxy_file = open(filename[:pos] + ".proxy.cpp", "w+")
        stub_file = open(filename[:pos] + ".stub.cpp", "w+")

        write_dependency(proxy_file, filename, True)
        write_dependency(stub_file, filename, False)


        # Loop printing each function signature
        for name, sig in decls["functions"].iteritems():
            # Python Array of all args (each is a hash with keys "name" and "type")
            args = sig["arguments"]
            argstrings = generate_argstring(args)

            # print the function signature
            print "%s %s(%s)" % (sig["return_type"], name, argstrings[0])

            write_send_function_name(proxy_file, sig["return_type"], name, argstrings[0])

            for a in args:
                write_send(proxy_file, a["type"], a["name"], 0, struct_attributes[a["type"]], '', True) # eg. "int x"
            
            write_recv(proxy_file, sig["return_type"], "result", 0, struct_attributes[sig["return_type"]], '')
            write_recv_done(proxy_file, name)
            
            write_stub_function(stub_file, sig["return_type"], name, argstrings[0], argstrings[1])
            write_send(stub_file, sig["return_type"], "result", 0, struct_attributes[a["type"]], '', False)
            write_send_done(stub_file)

        write_dispatch(stub_file, args, decls["functions"])

        write_extract_from_stream(proxy_file, True)
        write_extract_from_stream(stub_file, False)

    except Exception as e:
        print >> sys.stderr, "Usage: %s <idlfilename>" % sys.argv[0]


if __name__ == "__main__":
    main()

