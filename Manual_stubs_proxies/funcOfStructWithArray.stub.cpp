
#include "rpcstubhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

#include "funcOfStructWithArray.idl"

#define BUFSIZE 256
using namespace C150NETWORK;  // for all the comp150 utilities 

void extractFromStream(char *buffer, unsigned int bufSize);

Person __operation1(StructWithArrays s) {
  char doneBuffer[] = "DONE";
  // cout << "In switched Name\n" << orig.firstname << endl << orig.lastname << endl<< orig.age << endl;

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"funcOfStructWithArray.stub.cpp: invoking add()");
  Person p = operation1(s);
  // cout << "Result " << " first name: " << p.firstname << ", last name: " << p.lastname << ", age: " << p.age << endl;

  // Write the result struct to the client

  string temp = to_string(p.age) + '\0';
  const char* age_str = temp.c_str();
  p.firstname += '\0'; 
  p.lastname += '\0';
  RPCSTUBSOCKET->write(p.firstname.c_str(), strlen(p.firstname.c_str())+1); 
  RPCSTUBSOCKET->write(p.lastname.c_str(), strlen(p.lastname.c_str())+1); 
  RPCSTUBSOCKET->write(age_str, strlen(age_str)+1); 

  c150debug->printf(C150RPCDEBUG,"funcOfStructWithArray.stub.cpp: returned from structWithArray() -- responding to client");
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);

  return p;
}


//
//     __badFunction
//
//   Pseudo-stub for missing functions.
//
void __badFunction(const char *functionName) {
  char doneBuffer[5] = "BAD";  // to write magic value DONE + null
  c150debug->printf(C150RPCDEBUG,"funcOfStructWithArray.stub.cpp: received call for nonexistent function %s()",functionName);
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}


void dispatchFunction() {
  char functionNameBuffer[50];

  extractFromStream(functionNameBuffer,sizeof(functionNameBuffer));
  // Rebuild the struct with arrays and pass into function
  if (!RPCSTUBSOCKET-> eof()) {
    int aNum;
    Person pp[2];
    int age;
    string firstName;
    string lastName;

    char aNumBuf[50];
    extractFromStream(aNumBuf,sizeof(aNumBuf));
    aNum = stoi(aNumBuf);

    // Rebuild the people araray
    for (int i = 0; i < 2; i++) {
      char firstnameBuf[50];
      char lastnameBuf[50];
      char ageBuf[50];

      // Read original struct info from client
      extractFromStream(firstnameBuf,sizeof(firstnameBuf));
      extractFromStream(lastnameBuf,sizeof(lastnameBuf));
      extractFromStream(ageBuf,sizeof(ageBuf));
      age = stoi(ageBuf);
      firstName = string(firstnameBuf);
      lastName = string(lastnameBuf);

      pp[i].firstname = firstName;
      pp[i].lastname = lastName;
      pp[i].age = age;

    }

    // Reconstruct the original struct to pass into switch name function
    StructWithArrays s;
      s.aNumber = aNum;
      for (int i = 0; i < 2; i++)
        s.people[i] = pp[i];


    if (strcmp(functionNameBuffer,"operation1") == 0) {
      __operation1(s);
    }

    else
      __badFunction(functionNameBuffer);
  }
}

void extractFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;    // next char to read
  bool readnull;
  ssize_t readlen;             // amount of data read from socket
  
  //
  // Read a message from the stream
  // -1 in size below is to leave room for null
  //
  readnull = false;
  bufp = buffer;
  for (i=0; i< bufSize; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte
    // check for eof or error
    if (readlen == 0) {
      break;
    }
    // check for null and bump buffer pointer
    if (*bufp++ == '\0') {
      readnull = true;
      break;
    }
  }
  
  //
  // With TCP streams, we should never get a 0 length read
  // except with timeouts (which we're not setting in pingstreamserver)
  // or EOF
  //
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"simplefunction.stub: read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
      c150debug->printf(C150RPCDEBUG,"simplefunction.stub: EOF signaled on input");

    } else {
      throw C150Exception("simplefunction.stub: unexpected zero length read without eof");
    }
  }

  //
  // If we didn't get a null, input message was poorly formatted
  //
  else if(!readnull) 
    throw C150Exception("simplefunction.stub: method name not null terminated or too long");

  
  //
  // Note that eof may be set here for our caller to check
  //

}







