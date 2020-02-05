#include "rpcproxyhelper.h"

#include "c150debug.h"
#include "c150grading.h"
#include <fstream>
#include <string>
using namespace std;          // for C++ std library

using namespace C150NETWORK;  // for all the comp150 utilities 

#include "funcOfStructWith2dArray.idl"


// forward declarations
void setUpDebugLogging(const char *logname, int argc, char *argv[]);


void print_person(Person p) {
  cout << p.name[0] << endl << p.name[1] << endl << "STRENGTH =" << p.st.strength << endl << "INTEL =" << p.st.intel << endl;
  for (int a = 0; a < 2; ++a) 
      for (int b = 0; b < 2; ++b)
          for (int c = 0; c < 2; ++c)
              cout << p.st.num[a][b][c] << endl;
}

void print_struct(StructWith2dArray s) {
  cout << "ANUM =" << s.aNumber << endl;
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      print_person(s.people[i][j]);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                    Command line arguments
//
// The following are used as subscripts to argv, the command line arguments
// If we want to change the command line syntax, doing this
// symbolically makes it a bit easier.
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

const int serverArg = 1;     // server name is 1st arg


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                           main program
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 
int 
main(int argc, char *argv[]) {

     //
     //  Set up debug message logging
     //
     setUpDebugLogging("funcOfStructWith2dArray.txt",argc, argv);

     //
     // Make sure command line looks right
     //
     if (argc != 2) {
       fprintf(stderr,"Correct syntxt is: %s <servername> \n", argv[0]);
       exit(1);
     }

     //
     //  DO THIS FIRST OR YOUR ASSIGNMENT WON'T BE GRADED!
     //
     
     GRADEME(argc, argv);

     //
     //     Call the functions and see if they return
     //
     try {

    Stat st1 = {
      1.1,
      1.2,
      {
        {{1,2},{3,4}},
        {{5,6},{7,8}}
      }
    };

      Stat st2 = {
        2.1,
        2.2,
        {
          {{11,22},{33,44}},
          {{55,66},{77,88}}
        }
      };

      Stat st3 = {
        3.1,
        3.2,
        {
          {{111,222},{333,444}},
          {{555,666},{777,888}}
        }
      };

      Stat st4 = {
        4.1,
        4.2,
        {
          {{1111,2222},{3333,4444}},
          {{5555,6666},{7777,8888}}
        }
      };

      StructWith2dArray s1 = {
        100000, //aNumber
        {
        {{{"Runzte", "Si"}, 26, st1},
        {{"Drake", "Nguyen"}, 24, st2}},
        {{{"Runzte", "Si"}, 36, st3},
        {{"Drake", "Nguyen"}, 34, st4}}         
        } //people
       };

      StructWith2dArray s2 = {
        100000, //aNumber
        {
        {{{"Runzte", "Si"}, 26, st1},
        {{"Drake", "Nguyen"}, 24, st2}},
        {{{"Runzte", "Si"}, 36, st3},
        {{"Drake", "Nguyen"}, 34, st4}}         
        } //people
       };


      rpcproxyinitialize(argv[serverArg]);

      printf("Struct With Arrays s\n");
      StructWith2dArray result = operation1(s1, s2);
      Person result2 = operation2(s1, {{"Runzte", "Si"}, 26, st1});

      cout << "RESULT 1: \n";
      print_struct(result);
      cout << "\n\nRESULT 2: \n";
      print_person(result2);

    }
    //
    //  Handle networking errors -- for now, just print message and give up!
    //
    catch (C150Exception& e) {
      // Write to debug log
      c150debug->printf(C150ALWAYSLOG,"Caught C150Exception: %s\n",
      e.formattedExplanation().c_str());
      // In case we're logging to a file, write to the console too
      cerr << argv[0] << ": caught C150NetworkException: " << e.formattedExplanation() << endl;
    }

    return 0;
}




void setUpDebugLogging(const char *logname, int argc, char *argv[]) {
     ofstream *outstreamp = new ofstream(logname);
     DebugStream *filestreamp = new DebugStream(outstreamp);
     DebugStream::setDefaultLogger(filestreamp);

     //
     //  Put the program name and a timestamp on each line of the debug log.
     //
     c150debug->setPrefix(argv[0]);
     c150debug->enableTimestamp(); 

     c150debug->enableLogging(C150ALLDEBUG | C150RPCDEBUG | C150APPLICATION | C150NETWORKTRAFFIC | 
			      C150NETWORKDELIVERY); 
}
