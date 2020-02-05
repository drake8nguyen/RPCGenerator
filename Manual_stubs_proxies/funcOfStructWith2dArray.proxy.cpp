#include "rpcproxyhelper.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "c150grading.h"
using namespace std;
#include "funcOfStructWith2dArray.idl"
using namespace C150NETWORK;
void extractFromStream(char *buffer, unsigned int bufSize);

Person operation2(StructWith2dArray s1, Person p) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("operation2", strlen("operation2")+1);
	string _s1_aNumber = to_string(s1.aNumber) + '\0';
	RPCPROXYSOCKET->write(_s1_aNumber.c_str(), strlen(_s1_aNumber.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				s1.people[i][j].name[k] += '\0';
				RPCPROXYSOCKET->write(s1.people[i][j].name[k].c_str(), strlen(s1.people[i][j].name[k].c_str())+1);

			}

			string _s1_people_i__j__age = to_string(s1.people[i][j].age) + '\0';
			RPCPROXYSOCKET->write(_s1_people_i__j__age.c_str(), strlen(_s1_people_i__j__age.c_str())+1);

			string _s1_people_i__j__st_strength = to_string(s1.people[i][j].st.strength) + '\0';
			RPCPROXYSOCKET->write(_s1_people_i__j__st_strength.c_str(), strlen(_s1_people_i__j__st_strength.c_str())+1);

			string _s1_people_i__j__st_intel = to_string(s1.people[i][j].st.intel) + '\0';
			RPCPROXYSOCKET->write(_s1_people_i__j__st_intel.c_str(), strlen(_s1_people_i__j__st_intel.c_str())+1);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						string _s1_people_i__j__st_num_k__l__m_ = to_string(s1.people[i][j].st.num[k][l][m]) + '\0';
						RPCPROXYSOCKET->write(_s1_people_i__j__st_num_k__l__m_.c_str(), strlen(_s1_people_i__j__st_num_k__l__m_.c_str())+1);

					}

				}

			}

		}

	}

	for (int i = 0; i < 2; i++) {
		p.name[i] += '\0';
		RPCPROXYSOCKET->write(p.name[i].c_str(), strlen(p.name[i].c_str())+1);

	}

	string _p_age = to_string(p.age) + '\0';
	RPCPROXYSOCKET->write(_p_age.c_str(), strlen(_p_age.c_str())+1);

	string _p_st_strength = to_string(p.st.strength) + '\0';
	RPCPROXYSOCKET->write(_p_st_strength.c_str(), strlen(_p_st_strength.c_str())+1);

	string _p_st_intel = to_string(p.st.intel) + '\0';
	RPCPROXYSOCKET->write(_p_st_intel.c_str(), strlen(_p_st_intel.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				string _p_st_num_i__j__k_ = to_string(p.st.num[i][j][k]) + '\0';
				RPCPROXYSOCKET->write(_p_st_num_i__j__k_.c_str(), strlen(_p_st_num_i__j__k_.c_str())+1);

			}

		}

	}

	Person result;

	for (int i = 0; i < 2; i++) {
		char _result_name_i_Buf[50];
		extractFromStream(_result_name_i_Buf,sizeof(_result_name_i_Buf));
		result.name[i] = string(_result_name_i_Buf);

	}

	char _result_ageBuf[50];
	extractFromStream(_result_ageBuf,sizeof(_result_ageBuf));
	result.age = stoi(_result_ageBuf);

	char _result_st_strengthBuf[50];
	extractFromStream(_result_st_strengthBuf,sizeof(_result_st_strengthBuf));
	result.st.strength = stof(_result_st_strengthBuf);

	char _result_st_intelBuf[50];
	extractFromStream(_result_st_intelBuf,sizeof(_result_st_intelBuf));
	result.st.intel = stof(_result_st_intelBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				char _result_st_num_i__j__k_Buf[50];
				extractFromStream(_result_st_num_i__j__k_Buf,sizeof(_result_st_num_i__j__k_Buf));
				result.st.num[i][j][k] = stof(_result_st_num_i__j__k_Buf);

			}

		}

	}

	*GRADING << "Invocation sent, waiting for response to operation2()" << endl;
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: operation2() received invalid response from the server");
	}
	*GRADING << "operation2() successful return from remote call" << endl;
	return result;
}


StructWith2dArray operation1(StructWith2dArray s1, StructWith2dArray s2) {
	char readBuffer[5];
	RPCPROXYSOCKET->write("operation1", strlen("operation1")+1);
	string _s1_aNumber = to_string(s1.aNumber) + '\0';
	RPCPROXYSOCKET->write(_s1_aNumber.c_str(), strlen(_s1_aNumber.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				s1.people[i][j].name[k] += '\0';
				RPCPROXYSOCKET->write(s1.people[i][j].name[k].c_str(), strlen(s1.people[i][j].name[k].c_str())+1);

			}

			string _s1_people_i__j__age = to_string(s1.people[i][j].age) + '\0';
			RPCPROXYSOCKET->write(_s1_people_i__j__age.c_str(), strlen(_s1_people_i__j__age.c_str())+1);

			string _s1_people_i__j__st_strength = to_string(s1.people[i][j].st.strength) + '\0';
			RPCPROXYSOCKET->write(_s1_people_i__j__st_strength.c_str(), strlen(_s1_people_i__j__st_strength.c_str())+1);

			string _s1_people_i__j__st_intel = to_string(s1.people[i][j].st.intel) + '\0';
			RPCPROXYSOCKET->write(_s1_people_i__j__st_intel.c_str(), strlen(_s1_people_i__j__st_intel.c_str())+1);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						string _s1_people_i__j__st_num_k__l__m_ = to_string(s1.people[i][j].st.num[k][l][m]) + '\0';
						RPCPROXYSOCKET->write(_s1_people_i__j__st_num_k__l__m_.c_str(), strlen(_s1_people_i__j__st_num_k__l__m_.c_str())+1);

					}

				}

			}

		}

	}

	string _s2_aNumber = to_string(s2.aNumber) + '\0';
	RPCPROXYSOCKET->write(_s2_aNumber.c_str(), strlen(_s2_aNumber.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				s2.people[i][j].name[k] += '\0';
				RPCPROXYSOCKET->write(s2.people[i][j].name[k].c_str(), strlen(s2.people[i][j].name[k].c_str())+1);

			}

			string _s2_people_i__j__age = to_string(s2.people[i][j].age) + '\0';
			RPCPROXYSOCKET->write(_s2_people_i__j__age.c_str(), strlen(_s2_people_i__j__age.c_str())+1);

			string _s2_people_i__j__st_strength = to_string(s2.people[i][j].st.strength) + '\0';
			RPCPROXYSOCKET->write(_s2_people_i__j__st_strength.c_str(), strlen(_s2_people_i__j__st_strength.c_str())+1);

			string _s2_people_i__j__st_intel = to_string(s2.people[i][j].st.intel) + '\0';
			RPCPROXYSOCKET->write(_s2_people_i__j__st_intel.c_str(), strlen(_s2_people_i__j__st_intel.c_str())+1);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						string _s2_people_i__j__st_num_k__l__m_ = to_string(s2.people[i][j].st.num[k][l][m]) + '\0';
						RPCPROXYSOCKET->write(_s2_people_i__j__st_num_k__l__m_.c_str(), strlen(_s2_people_i__j__st_num_k__l__m_.c_str())+1);

					}

				}

			}

		}

	}

	StructWith2dArray result;

	char _result_aNumberBuf[50];
	extractFromStream(_result_aNumberBuf,sizeof(_result_aNumberBuf));
	result.aNumber = stoi(_result_aNumberBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				char _result_people_i__j__name_k_Buf[50];
				extractFromStream(_result_people_i__j__name_k_Buf,sizeof(_result_people_i__j__name_k_Buf));
				result.people[i][j].name[k] = string(_result_people_i__j__name_k_Buf);

			}

			char _result_people_i__j__ageBuf[50];
			extractFromStream(_result_people_i__j__ageBuf,sizeof(_result_people_i__j__ageBuf));
			result.people[i][j].age = stoi(_result_people_i__j__ageBuf);

			char _result_people_i__j__st_strengthBuf[50];
			extractFromStream(_result_people_i__j__st_strengthBuf,sizeof(_result_people_i__j__st_strengthBuf));
			result.people[i][j].st.strength = stof(_result_people_i__j__st_strengthBuf);

			char _result_people_i__j__st_intelBuf[50];
			extractFromStream(_result_people_i__j__st_intelBuf,sizeof(_result_people_i__j__st_intelBuf));
			result.people[i][j].st.intel = stof(_result_people_i__j__st_intelBuf);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						char _result_people_i__j__st_num_k__l__m_Buf[50];
						extractFromStream(_result_people_i__j__st_num_k__l__m_Buf,sizeof(_result_people_i__j__st_num_k__l__m_Buf));
						result.people[i][j].st.num[k][l][m] = stof(_result_people_i__j__st_num_k__l__m_Buf);

					}

				}

			}

		}

	}

	*GRADING << "Invocation sent, waiting for response to operation1()" << endl;
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("funcOfStructWith2dArray.proxy: operation1() received invalid response from the server");
	}
	*GRADING << "operation1() successful return from remote call" << endl;
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
