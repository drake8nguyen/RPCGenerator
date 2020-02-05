#include "rpcproxyhelper.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "c150grading.h"
using namespace std;
#include "floatarithmetic.idl"
using namespace C150NETWORK;
void extractFromStream(char *buffer, unsigned int bufSize);

float multiply(float x, float y) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("multiply", strlen("multiply")+1);
	string _x = to_string(x) + '\0';
	RPCPROXYSOCKET->write(_x.c_str(), strlen(_x.c_str())+1);

	string _y = to_string(y) + '\0';
	RPCPROXYSOCKET->write(_y.c_str(), strlen(_y.c_str())+1);

	char _resultBuf[50];
	extractFromStream(_resultBuf,sizeof(_resultBuf));
	int result = stof(_resultBuf);

	*GRADING << "Invocation sent, waiting for response to multiply()" << endl;
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: multiply() received invalid response from the server");
	}
	*GRADING << "multiply() successful return from remote call" << endl;
	return result;
}


float add(float x, float y) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("add", strlen("add")+1);
	string _x = to_string(x) + '\0';
	RPCPROXYSOCKET->write(_x.c_str(), strlen(_x.c_str())+1);

	string _y = to_string(y) + '\0';
	RPCPROXYSOCKET->write(_y.c_str(), strlen(_y.c_str())+1);

	char _resultBuf[50];
	extractFromStream(_resultBuf,sizeof(_resultBuf));
	int result = stof(_resultBuf);

	*GRADING << "Invocation sent, waiting for response to add()" << endl;
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: add() received invalid response from the server");
	}
	*GRADING << "add() successful return from remote call" << endl;
	return result;
}


float subtract(float x, float y) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("subtract", strlen("subtract")+1);
	string _x = to_string(x) + '\0';
	RPCPROXYSOCKET->write(_x.c_str(), strlen(_x.c_str())+1);

	string _y = to_string(y) + '\0';
	RPCPROXYSOCKET->write(_y.c_str(), strlen(_y.c_str())+1);

	char _resultBuf[50];
	extractFromStream(_resultBuf,sizeof(_resultBuf));
	int result = stof(_resultBuf);

	*GRADING << "Invocation sent, waiting for response to subtract()" << endl;
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: subtract() received invalid response from the server");
	}
	*GRADING << "subtract() successful return from remote call" << endl;
	return result;
}


float divide(float x, float y) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("divide", strlen("divide")+1);
	string _x = to_string(x) + '\0';
	RPCPROXYSOCKET->write(_x.c_str(), strlen(_x.c_str())+1);

	string _y = to_string(y) + '\0';
	RPCPROXYSOCKET->write(_y.c_str(), strlen(_y.c_str())+1);

	char _resultBuf[50];
	extractFromStream(_resultBuf,sizeof(_resultBuf));
	int result = stof(_resultBuf);

	*GRADING << "Invocation sent, waiting for response to divide()" << endl;
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: divide() received invalid response from the server");
	}
	*GRADING << "divide() successful return from remote call" << endl;
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
	*GRADING << "read zero length message, checking EOF" << endl;
		if (RPCPROXYSOCKET-> eof()) {
	*GRADING << "EOF signaled on input" << endl;
		} else {
	*GRADING << "unexpected zero length read without eof" << endl;
		}
	}
	else if(!readnull)
		throw C150Exception("method name not null terminated or too long");
}
