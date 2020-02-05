

#include "rpcproxyhelper.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//    Global variable where proxies can find socket.
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

C150StreamSocket *RPCPROXYSOCKET;
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                rpcproxyinitialize
//
//     Opens the socket and leaves it in global variable.
//     Note that the socket call may throw an exception 
//     which is NOT caught here.
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void rpcproxyinitialize(char *servername) {

  c150debug->printf(C150RPCDEBUG,"rpcproxyinitialize: Creating C150StreamSocket");
  RPCPROXYSOCKET = new C150StreamSocket();

  // Tell the Streamsocket which server to talk to
  // Note that the port number is defaulted according to
  // student logon by the COMP 150-IDS framework
  RPCPROXYSOCKET -> connect(servername);  
}
