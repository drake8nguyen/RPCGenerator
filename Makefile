# Do all C++ compies with g++
CPP = g++

# change following line if your rpgenerate is not in current directory
RPCGEN = ./rpcgenerate


C150LIB = $(COMP117)/files/c150Utils/
C150AR = $(C150LIB)c150ids.a

# RPC framework is shared archive
C150IDSRPC = $(COMP117)/files/RPC.framework/
C150IDSRPCAR = $(C150IDSRPC)c150idsrpc.a

CPPFLAGS = -g -Wall -Werror -I$(C150IDSRPC) -I$(C150LIB)
# CPPFLAGS = -g -Wall -Werror  -I$(C150LIB)


LDFLAGS = 
INCLUDES = $(C150LIB)c150streamsocket.h $(C150LIB)c150network.h $(C150LIB)c150exceptions.h $(C150LIB)c150debug.h $(C150LIB)c150utility.h $(C150LIB)c150grading.h $(C150IDSRPC)IDLToken.h $(C150IDSRPC)tokenizeddeclarations.h  $(C150IDSRPC)tokenizeddeclaration.h $(C150IDSRPC)declarations.h $(C150IDSRPC)declaration.h $(C150IDSRPC)functiondeclaration.h $(C150IDSRPC)typedeclaration.h $(C150IDSRPC)arg_or_member_declaration.h rpcproxyhelper.h rpcstubhelper.h 

all: idldeclarationtst idl_to_json 
#funcOfStructWith2dArrayclient funcOfStructWith2dArrayserver arithmeticclient arithmeticserver floatarithmeticclient floatarithmeticserver



# arithmeticclient: arithmeticclient.o rpcproxyhelper.o arithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
# 	$(CPP) -o arithmeticclient arithmeticclient.o rpcproxyhelper.o arithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# arithmeticserver: arithmetic.stub.o rpcserver.o rpcstubhelper.o arithmetic.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
# 	$(CPP) -o arithmeticserver rpcserver.o arithmetic.stub.o arithmetic.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 

# floatarithmeticclient: floatarithmeticclient.o rpcproxyhelper.o floatarithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
# 	$(CPP) -o floatarithmeticclient floatarithmeticclient.o rpcproxyhelper.o floatarithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# floatarithmeticserver: floatarithmetic.stub.o rpcserver.o rpcstubhelper.o floatarithmetic.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
# 	$(CPP) -o floatarithmeticserver rpcserver.o floatarithmetic.stub.o floatarithmetic.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 


# funcOfStructWith2dArrayclient: funcOfStructWith2dArrayclient.o rpcproxyhelper.o funcOfStructWith2dArray.proxy.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
# 	$(CPP) -o funcOfStructWith2dArrayclient funcOfStructWith2dArrayclient.o rpcproxyhelper.o funcOfStructWith2dArray.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# funcOfStructWith2dArrayserver: funcOfStructWith2dArray.stub.o rpcserver.o rpcstubhelper.o funcOfStructWith2dArray.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
# 	$(CPP) -o funcOfStructWith2dArrayserver rpcserver.o funcOfStructWith2dArray.stub.o funcOfStructWith2dArray.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 



########################################################################
#
#          Compile the rpcgenerate program
#
#    COMMENT THIS RULE IF YOU ARE USING PYTHON OR RUBY TO
#    IMPLEMENT YOUR rpcgenerate program.
#
########################################################################

# Compile the rpcgenerate program
rpcgenerate: Makefile rpcgenerate.o $(C150AR) $(C150IDSRPCAR) $(INCLUDES)
	$(CPP) -o rpcgenerate rpcgenerate.o $(C150AR) $(C150IDSRPCAR)




idldeclarationtst: idldeclarationtst.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o idldeclarationtst idldeclarationtst.o $(C150AR) $(C150IDSRPCAR) 



idl_to_json: idl_to_json.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o idl_to_json idl_to_json.o $(C150AR) $(C150IDSRPCAR) 



%.json:%.idl idl_to_json
	     idl_to_json $< > $@


# make .o from .cpp

%.o:%.cpp  $(INCLUDES)
	$(CPP) -c  $(CPPFLAGS) $< 



# clean up everything we build dynamically (probably missing .cpps from .idl)
clean:
	 rm -f idldeclarationtst idl_to_json *.o *.json *.pyc


