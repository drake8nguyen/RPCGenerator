
#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include <stdlib.h>
#include <string>
using namespace std;

#include "switchName.idl"


using namespace C150NETWORK;  // for all the comp150 utilities 
void extractFromStream(char *buffer, unsigned int bufSize);


void switchName(Person &orig) {
  char readBuffer[5];  
  RPCPROXYSOCKET->write("switchName", strlen("switchName")+1); // write function name including null


  //  Original struct
  //  Person p = {
  //    "Drake", //firstname
  //    "Nguyen", //lastname
  //    24 //age
  //  };

  // Sending the struct over to the server
  orig.firstname += '\0'; 
  RPCPROXYSOCKET->write(orig.firstname.c_str(), strlen(orig.firstname.c_str())+1); 
  orig.lastname += '\0';
  RPCPROXYSOCKET->write(orig.lastname.c_str(), strlen(orig.lastname.c_str())+1);
  const char* age_str = to_string(orig.age).c_str();
  RPCPROXYSOCKET->write(age_str, strlen(age_str)+1); 



  // pack function name and arguments into buffer
  c150debug->printf(C150RPCDEBUG,"arithmeticclient.proxy.cpp: switchName() invoked");
  

  //
  // Read the modified struct from server
  //

  char firstnameBuf[50];
  char lastnameBuf[50];
  char ageBuf[50];

  // The response from the server
  extractFromStream(firstnameBuf,sizeof(firstnameBuf));
  cout << firstnameBuf << endl;
  extractFromStream(lastnameBuf,sizeof(lastnameBuf));
  cout << lastnameBuf << endl;
  extractFromStream(ageBuf,sizeof(ageBuf));
  cout << ageBuf << endl;

  // Convert to string and then modify the original struct
  string newFirstName(firstnameBuf);
  string newLastName(lastnameBuf);
  orig.firstname = newFirstName;
  orig.lastname = newLastName;
  orig.age = stoi(ageBuf);

  c150debug->printf(C150RPCDEBUG,"arithmeticclient.proxy.cpp: switchName() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("arithmeticclient.proxy: add() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: add() successful return from remote call");
  
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
    readlen = RPCPROXYSOCKET-> read(bufp, 1);  // read a byte
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
    if (RPCPROXYSOCKET-> eof()) {
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