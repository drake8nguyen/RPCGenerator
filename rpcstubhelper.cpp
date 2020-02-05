

#include "rpcstubhelper.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//    Global variable where proxies can find socket.
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

C150StreamSocket *RPCSTUBSOCKET;
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                rpcstubinitialize
//
//     Opens the socket and leaves it in global variable.
//     Put it in listening state.
//     Note that the socket call may throw an exception 
//     which is NOT caught here.
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void rpcstubinitialize() {

  // create new socket
  c150debug->printf(C150RPCDEBUG,"rpcstubinitialize: Creating C150StreamSocket");
  RPCSTUBSOCKET = new C150StreamSocket();

  // Tell the OS to start allowing connections
  // The application will pick those up one at a time by doing accept calls
  RPCSTUBSOCKET -> listen();  
}
