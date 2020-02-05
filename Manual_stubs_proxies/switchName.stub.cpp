
#include "rpcstubhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

#include "switchName.idl"

#define BUFSIZE 256
using namespace C150NETWORK;  // for all the comp150 utilities 

void extractFromStream(char *buffer, unsigned int bufSize);

void __switchName(Person &orig) {
  char doneBuffer[] = "DONE";
  cout << "In switched Name\n" << orig.firstname << endl << orig.lastname << endl<< orig.age << endl;

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking add()");
  switchName(orig);

  cout << "Done switched Name\n" << orig.firstname << endl << orig.lastname << endl<< orig.age << endl;

  // Write the modified struct to the client
  const char* age_str = to_string(orig.age).c_str();
  RPCSTUBSOCKET->write(orig.firstname.c_str(), strlen(orig.firstname.c_str())+1); 
  RPCSTUBSOCKET->write(orig.lastname.c_str(), strlen(orig.lastname.c_str())+1); 
  RPCSTUBSOCKET->write(to_string(orig.age).c_str(), strlen(age_str)+1); 

  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  add() -- responding to client");
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);

}


//
//     __badFunction
//
//   Pseudo-stub for missing functions.
//
void __badFunction(const char *functionName) {
  char doneBuffer[5] = "BAD";  // to write magic value DONE + null


  //
  // Send the response to the client indicating bad function
  //

  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: received call for nonexistent function %s()",functionName);
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}


void dispatchFunction() {
  // cout << "Dispatched" << endl;
  char functionNameBuffer[50];
  char firstnameBuf[50];
  char lastnameBuf[50];
  char ageBuf[50];


  // Read original struct info from client
  extractFromStream(functionNameBuffer,sizeof(functionNameBuffer));
  cout << "1" << endl;
  cout << functionNameBuffer << endl;
  extractFromStream(firstnameBuf,sizeof(firstnameBuf));
  cout << "2" << endl;
  cout << firstnameBuf << endl;
  extractFromStream(lastnameBuf,sizeof(lastnameBuf));
  cout << "3" << endl;
  cout << lastnameBuf << endl;
  extractFromStream(ageBuf,sizeof(ageBuf));
  cout << "4" << endl;
  cout << ageBuf << endl;


  int age = stoi(ageBuf);
  string firstName(firstnameBuf);
  string lastName(lastnameBuf);

  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(functionNameBuffer,"switchName") == 0) {
      // Reconstruct the original struct to pass into switch name function
      Person orig = {
        firstName, //firstname
        lastName, //lastname
        age //age
      };
      __switchName(orig);
      
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







