#include "rpcstubhelper.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "c150grading.h"
using namespace std;
#include "floatarithmetic.idl"
using namespace C150NETWORK;
void extractFromStream(char *buffer, unsigned int bufSize);

float __multiply(float x, float y) {
	char doneBuffer[] = "DONE";
	*GRADING << "Invoking: multiply()" << endl;
	float result = multiply(x, y);
	string _result = to_string(result) + '\0';
	RPCSTUBSOCKET->write(_result.c_str(), strlen(_result.c_str())+1);

	*GRADING << "Return from function -- responding to client" << endl;
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	return result;
}
float __add(float x, float y) {
	char doneBuffer[] = "DONE";
	*GRADING << "Invoking: add()" << endl;
	float result = add(x, y);
	string _result = to_string(result) + '\0';
	RPCSTUBSOCKET->write(_result.c_str(), strlen(_result.c_str())+1);

	*GRADING << "Return from function -- responding to client" << endl;
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	return result;
}
float __subtract(float x, float y) {
	char doneBuffer[] = "DONE";
	*GRADING << "Invoking: subtract()" << endl;
	float result = subtract(x, y);
	string _result = to_string(result) + '\0';
	RPCSTUBSOCKET->write(_result.c_str(), strlen(_result.c_str())+1);

	*GRADING << "Return from function -- responding to client" << endl;
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	return result;
}
float __divide(float x, float y) {
	char doneBuffer[] = "DONE";
	*GRADING << "Invoking: divide()" << endl;
	float result = divide(x, y);
	string _result = to_string(result) + '\0';
	RPCSTUBSOCKET->write(_result.c_str(), strlen(_result.c_str())+1);

	*GRADING << "Return from function -- responding to client" << endl;
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	return result;
}
void __badFunction(const char *functionName) {
	char doneBuffer[5] = "BAD";
	*GRADING << "received call for nonexistent function " << functionName << "()" << endl;
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}
void dispatchFunction() {
	char functionNameBuffer[50];
	extractFromStream(functionNameBuffer,sizeof(functionNameBuffer));
	if (!RPCSTUBSOCKET-> eof()) {
		if (strcmp(functionNameBuffer,"multiply") == 0) {
	char _xBuf[50];
	extractFromStream(_xBuf,sizeof(_xBuf));
	int x = stof(_xBuf);

	char _yBuf[50];
	extractFromStream(_yBuf,sizeof(_yBuf));
	int y = stof(_yBuf);

			__multiply(x, y);
		} else
		if (strcmp(functionNameBuffer,"add") == 0) {
	char _xBuf[50];
	extractFromStream(_xBuf,sizeof(_xBuf));
	int x = stof(_xBuf);

	char _yBuf[50];
	extractFromStream(_yBuf,sizeof(_yBuf));
	int y = stof(_yBuf);

			__add(x, y);
		} else
		if (strcmp(functionNameBuffer,"subtract") == 0) {
	char _xBuf[50];
	extractFromStream(_xBuf,sizeof(_xBuf));
	int x = stof(_xBuf);

	char _yBuf[50];
	extractFromStream(_yBuf,sizeof(_yBuf));
	int y = stof(_yBuf);

			__subtract(x, y);
		} else
		if (strcmp(functionNameBuffer,"divide") == 0) {
	char _xBuf[50];
	extractFromStream(_xBuf,sizeof(_xBuf));
	int x = stof(_xBuf);

	char _yBuf[50];
	extractFromStream(_yBuf,sizeof(_yBuf));
	int y = stof(_yBuf);

			__divide(x, y);
		} else
			__badFunction(functionNameBuffer);
		}
}

void extractFromStream(char *buffer, unsigned int bufSize) {
	unsigned int i;
	char *bufp;
	bool readnull;
	ssize_t readlen;
	readnull = false;
	bufp = buffer;
	for (i=0; i< bufSize; i++) {
		readlen = RPCSTUBSOCKET-> read(bufp, 1);
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
		if (RPCSTUBSOCKET-> eof()) {
	*GRADING << "EOF signaled on input" << endl;
		} else {
	*GRADING << "unexpected zero length read without eof" << endl;
		}
	}
	else if(!readnull)
		throw C150Exception("method name not null terminated or too long");
}
