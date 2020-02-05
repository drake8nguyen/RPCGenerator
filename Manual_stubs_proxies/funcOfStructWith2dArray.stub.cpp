#include "rpcstubhelper.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "c150grading.h"
using namespace std;
#include "funcOfStructWith2dArray.idl"
using namespace C150NETWORK;
void extractFromStream(char *buffer, unsigned int bufSize);

Person __operation2(StructWith2dArray s1, Person p) {
	char doneBuffer[] = "DONE";
	*GRADING << "Invoking: operation2()" << endl;
	Person result = operation2(s1, p);
	for (int i = 0; i < 2; i++) {
		result.name[i] += '\0';
		RPCSTUBSOCKET->write(result.name[i].c_str(), strlen(result.name[i].c_str())+1);

	}

	string _result_age = to_string(result.age) + '\0';
	RPCSTUBSOCKET->write(_result_age.c_str(), strlen(_result_age.c_str())+1);

	string _result_st_strength = to_string(result.st.strength) + '\0';
	RPCSTUBSOCKET->write(_result_st_strength.c_str(), strlen(_result_st_strength.c_str())+1);

	string _result_st_intel = to_string(result.st.intel) + '\0';
	RPCSTUBSOCKET->write(_result_st_intel.c_str(), strlen(_result_st_intel.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				string _result_st_num_i__j__k_ = to_string(result.st.num[i][j][k]) + '\0';
				RPCSTUBSOCKET->write(_result_st_num_i__j__k_.c_str(), strlen(_result_st_num_i__j__k_.c_str())+1);

			}

		}

	}

	*GRADING << "Return from function -- responding to client" << endl;
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	return result;
}
StructWith2dArray __operation1(StructWith2dArray s1, StructWith2dArray s2) {
	char doneBuffer[] = "DONE";
	*GRADING << "Invoking: operation1()" << endl;
	StructWith2dArray result = operation1(s1, s2);
	string _result_aNumber = to_string(result.aNumber) + '\0';
	RPCSTUBSOCKET->write(_result_aNumber.c_str(), strlen(_result_aNumber.c_str())+1);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				result.people[i][j].name[k] += '\0';
				RPCSTUBSOCKET->write(result.people[i][j].name[k].c_str(), strlen(result.people[i][j].name[k].c_str())+1);

			}

			string _result_people_i__j__age = to_string(result.people[i][j].age) + '\0';
			RPCSTUBSOCKET->write(_result_people_i__j__age.c_str(), strlen(_result_people_i__j__age.c_str())+1);

			string _result_people_i__j__st_strength = to_string(result.people[i][j].st.strength) + '\0';
			RPCSTUBSOCKET->write(_result_people_i__j__st_strength.c_str(), strlen(_result_people_i__j__st_strength.c_str())+1);

			string _result_people_i__j__st_intel = to_string(result.people[i][j].st.intel) + '\0';
			RPCSTUBSOCKET->write(_result_people_i__j__st_intel.c_str(), strlen(_result_people_i__j__st_intel.c_str())+1);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						string _result_people_i__j__st_num_k__l__m_ = to_string(result.people[i][j].st.num[k][l][m]) + '\0';
						RPCSTUBSOCKET->write(_result_people_i__j__st_num_k__l__m_.c_str(), strlen(_result_people_i__j__st_num_k__l__m_.c_str())+1);

					}

				}

			}

		}

	}

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
		if (strcmp(functionNameBuffer,"operation2") == 0) {
	StructWith2dArray s1;

	char _s1_aNumberBuf[50];
	extractFromStream(_s1_aNumberBuf,sizeof(_s1_aNumberBuf));
	s1.aNumber = stoi(_s1_aNumberBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				char _s1_people_i__j__name_k_Buf[50];
				extractFromStream(_s1_people_i__j__name_k_Buf,sizeof(_s1_people_i__j__name_k_Buf));
				s1.people[i][j].name[k] = string(_s1_people_i__j__name_k_Buf);

			}

			char _s1_people_i__j__ageBuf[50];
			extractFromStream(_s1_people_i__j__ageBuf,sizeof(_s1_people_i__j__ageBuf));
			s1.people[i][j].age = stoi(_s1_people_i__j__ageBuf);

			char _s1_people_i__j__st_strengthBuf[50];
			extractFromStream(_s1_people_i__j__st_strengthBuf,sizeof(_s1_people_i__j__st_strengthBuf));
			s1.people[i][j].st.strength = stof(_s1_people_i__j__st_strengthBuf);

			char _s1_people_i__j__st_intelBuf[50];
			extractFromStream(_s1_people_i__j__st_intelBuf,sizeof(_s1_people_i__j__st_intelBuf));
			s1.people[i][j].st.intel = stof(_s1_people_i__j__st_intelBuf);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						char _s1_people_i__j__st_num_k__l__m_Buf[50];
						extractFromStream(_s1_people_i__j__st_num_k__l__m_Buf,sizeof(_s1_people_i__j__st_num_k__l__m_Buf));
						s1.people[i][j].st.num[k][l][m] = stof(_s1_people_i__j__st_num_k__l__m_Buf);

					}

				}

			}

		}

	}

	Person p;

	for (int i = 0; i < 2; i++) {
		char _p_name_i_Buf[50];
		extractFromStream(_p_name_i_Buf,sizeof(_p_name_i_Buf));
		p.name[i] = string(_p_name_i_Buf);

	}

	char _p_ageBuf[50];
	extractFromStream(_p_ageBuf,sizeof(_p_ageBuf));
	p.age = stoi(_p_ageBuf);

	char _p_st_strengthBuf[50];
	extractFromStream(_p_st_strengthBuf,sizeof(_p_st_strengthBuf));
	p.st.strength = stof(_p_st_strengthBuf);

	char _p_st_intelBuf[50];
	extractFromStream(_p_st_intelBuf,sizeof(_p_st_intelBuf));
	p.st.intel = stof(_p_st_intelBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				char _p_st_num_i__j__k_Buf[50];
				extractFromStream(_p_st_num_i__j__k_Buf,sizeof(_p_st_num_i__j__k_Buf));
				p.st.num[i][j][k] = stof(_p_st_num_i__j__k_Buf);

			}

		}

	}

			__operation2(s1, p);
		} else
		if (strcmp(functionNameBuffer,"operation1") == 0) {
	StructWith2dArray s1;

	char _s1_aNumberBuf[50];
	extractFromStream(_s1_aNumberBuf,sizeof(_s1_aNumberBuf));
	s1.aNumber = stoi(_s1_aNumberBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				char _s1_people_i__j__name_k_Buf[50];
				extractFromStream(_s1_people_i__j__name_k_Buf,sizeof(_s1_people_i__j__name_k_Buf));
				s1.people[i][j].name[k] = string(_s1_people_i__j__name_k_Buf);

			}

			char _s1_people_i__j__ageBuf[50];
			extractFromStream(_s1_people_i__j__ageBuf,sizeof(_s1_people_i__j__ageBuf));
			s1.people[i][j].age = stoi(_s1_people_i__j__ageBuf);

			char _s1_people_i__j__st_strengthBuf[50];
			extractFromStream(_s1_people_i__j__st_strengthBuf,sizeof(_s1_people_i__j__st_strengthBuf));
			s1.people[i][j].st.strength = stof(_s1_people_i__j__st_strengthBuf);

			char _s1_people_i__j__st_intelBuf[50];
			extractFromStream(_s1_people_i__j__st_intelBuf,sizeof(_s1_people_i__j__st_intelBuf));
			s1.people[i][j].st.intel = stof(_s1_people_i__j__st_intelBuf);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						char _s1_people_i__j__st_num_k__l__m_Buf[50];
						extractFromStream(_s1_people_i__j__st_num_k__l__m_Buf,sizeof(_s1_people_i__j__st_num_k__l__m_Buf));
						s1.people[i][j].st.num[k][l][m] = stof(_s1_people_i__j__st_num_k__l__m_Buf);

					}

				}

			}

		}

	}

	StructWith2dArray s2;

	char _s2_aNumberBuf[50];
	extractFromStream(_s2_aNumberBuf,sizeof(_s2_aNumberBuf));
	s2.aNumber = stoi(_s2_aNumberBuf);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				char _s2_people_i__j__name_k_Buf[50];
				extractFromStream(_s2_people_i__j__name_k_Buf,sizeof(_s2_people_i__j__name_k_Buf));
				s2.people[i][j].name[k] = string(_s2_people_i__j__name_k_Buf);

			}

			char _s2_people_i__j__ageBuf[50];
			extractFromStream(_s2_people_i__j__ageBuf,sizeof(_s2_people_i__j__ageBuf));
			s2.people[i][j].age = stoi(_s2_people_i__j__ageBuf);

			char _s2_people_i__j__st_strengthBuf[50];
			extractFromStream(_s2_people_i__j__st_strengthBuf,sizeof(_s2_people_i__j__st_strengthBuf));
			s2.people[i][j].st.strength = stof(_s2_people_i__j__st_strengthBuf);

			char _s2_people_i__j__st_intelBuf[50];
			extractFromStream(_s2_people_i__j__st_intelBuf,sizeof(_s2_people_i__j__st_intelBuf));
			s2.people[i][j].st.intel = stof(_s2_people_i__j__st_intelBuf);

			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						char _s2_people_i__j__st_num_k__l__m_Buf[50];
						extractFromStream(_s2_people_i__j__st_num_k__l__m_Buf,sizeof(_s2_people_i__j__st_num_k__l__m_Buf));
						s2.people[i][j].st.num[k][l][m] = stof(_s2_people_i__j__st_num_k__l__m_Buf);

					}

				}

			}

		}

	}

			__operation1(s1, s2);
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
