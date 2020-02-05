#include "rpcproxyhelper.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"
using namespace std;
#include "funcOfStructWith2dArray.idl"
using namespace C150NETWORK;
void extractFromStream(char *buffer, unsigned int bufSize);

StructWith2dArray operation2(StructWith2dArray s) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("operation2", strlen("operation2")+1);
	string temp = to_string(s.aNumber) + '\0';
	RPCPROXYSOCKET->write(temp.c_str(), strlen(temp.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			s.people[i][j].firstname += '\0';
			RPCPROXYSOCKET->write(s.people[i][j].firstname.c_str(), strlen(s.people[i][j].firstname.c_str())+1);

			s.people[i][j].lastname += '\0';
			RPCPROXYSOCKET->write(s.people[i][j].lastname.c_str(), strlen(s.people[i][j].lastname.c_str())+1);

			string temp = to_string(s.people[i][j].age) + '\0';
			RPCPROXYSOCKET->write(temp.c_str(), strlen(temp.c_str())+1);

		}

	}



	// The response from the server

	StructWith2dArray result;

	char aNumberBuf[50];
	extractFromStream(aNumberBuf,sizeof(aNumberBuf));
	result.aNumber = stoi(aNumberBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			char firstnameBuf[50];
			extractFromStream(firstnameBuf,sizeof(firstnameBuf));
			result.people[i][j].firstname = string(firstnameBuf);

			char lastnameBuf[50];
			extractFromStream(lastnameBuf,sizeof(lastnameBuf));
			result.people[i][j].lastname = string(lastnameBuf);

			char ageBuf[50];
			extractFromStream(ageBuf,sizeof(ageBuf));
			result.people[i][j].age = stoi(ageBuf);

		}

	}

	c150debug->printf(C150RPCDEBUG,"funcOfStructWith2dArray.proxy.cpp: operation1() invocation sent, waiting for response");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: add() received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"funcOfStructWith2dArray.proxy.cpp: add() successful return from remote call");
	return result;
}


StructWith2dArray operation1(StructWith2dArray s) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("operation1", strlen("operation1")+1);
	string temp = to_string(s.aNumber) + '\0';
	RPCPROXYSOCKET->write(temp.c_str(), strlen(temp.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			s.people[i][j].firstname += '\0';
			RPCPROXYSOCKET->write(s.people[i][j].firstname.c_str(), strlen(s.people[i][j].firstname.c_str())+1);

			s.people[i][j].lastname += '\0';
			RPCPROXYSOCKET->write(s.people[i][j].lastname.c_str(), strlen(s.people[i][j].lastname.c_str())+1);

			string temp = to_string(s.people[i][j].age) + '\0';
			RPCPROXYSOCKET->write(temp.c_str(), strlen(temp.c_str())+1);

		}

	}



	// The response from the server

	StructWith2dArray result;

	char aNumberBuf[50];
	extractFromStream(aNumberBuf,sizeof(aNumberBuf));
	result.aNumber = stoi(aNumberBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			char firstnameBuf[50];
			extractFromStream(firstnameBuf,sizeof(firstnameBuf));
			result.people[i][j].firstname = string(firstnameBuf);

			char lastnameBuf[50];
			extractFromStream(lastnameBuf,sizeof(lastnameBuf));
			result.people[i][j].lastname = string(lastnameBuf);

			char ageBuf[50];
			extractFromStream(ageBuf,sizeof(ageBuf));
			result.people[i][j].age = stoi(ageBuf);

		}

	}

	c150debug->printf(C150RPCDEBUG,"funcOfStructWith2dArray.proxy.cpp: operation1() invocation sent, waiting for response");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: add() received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"funcOfStructWith2dArray.proxy.cpp: add() successful return from remote call");
	return result;
}


void extractFromStream(char *buffer, unsigned int bufSize) {
	unsigned int i;
	char *bufp;
	bool readnull;
	ssize_t readlen;
	readnull = false;
	bufp = buffer;
	for (i=0; i< bufSize; i++) {
		readlen = RPCPROXYSOCKET-> read(bufp, 1);
		if (readlen == 0) {
			break;
		}
		if (*bufp++ == '\0') {
			readnull = true;
			break;
		}
	}
	if (readlen == 0) {
		c150debug->printf(C150RPCDEBUG,"funcOfStructWith2dArray.stub: read zero length message, checking EOF");
		if (RPCPROXYSOCKET-> eof()) {
			c150debug->printf(C150RPCDEBUG,"funcOfStructWith2dArray.stub: EOF signaled on input");
		} else {
			throw C150Exception("funcOfStructWith2dArray.stub: unexpected zero length read without eof");
		}
	}
	else if(!readnull)
		throw C150Exception("funcOfStructWith2dArray.stub: method name not null terminated or too long");
}
