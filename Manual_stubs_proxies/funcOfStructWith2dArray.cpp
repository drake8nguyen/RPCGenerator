#include <string>
using namespace std;
#include "funcOfStructWith2dArray.idl"
#include <iostream>

StructWith2dArray operation1(StructWith2dArray s1, StructWith2dArray s2) {

    for (int i = 0; i < 2; ++i) 
        for (int j = 0; j < 2; ++j) {
            s1.people[i][j].name[0] += s2.people[i][j].name[0];
            s1.people[i][j].name[1] += s2.people[i][j].name[1];

            s1.people[i][j].age += s2.people[i][j].age;

            s1.people[i][j].st.strength += s2.people[i][j].st.strength;
            s1.people[i][j].st.intel += s2.people[i][j].st.intel;
            for (int a = 0; a < 2; ++a) 
                for (int b = 0; b < 2; ++b)
                    for (int c = 0; c < 2; ++c)
                        s1.people[i][j].st.num[a][b][c] += s2.people[i][j].st.num[a][b][c];
        }
    s1.aNumber += s2.aNumber;
    return s1;
}


Person operation2(StructWith2dArray s1, Person p) {
    cout << p.name[0] << endl << p.name[1] << endl << p.st.strength << endl << p.st.intel;
    for (int a = 0; a < 2; ++a) 
        for (int b = 0; b < 2; ++b)
            for (int c = 0; c < 2; ++c)
                cout << p.st.num[a][b][c] << endl;

    Stat st1 = {
        12414.4252,
        1134135.2134134,
        {
          {{1134134,2134314},{314134,4464}},
          {{5134314,6134134},{7134314,8235235}}
        }
      };

    Person res = {
        {"Lionel", "Messi"}, 26, st1
    };

    s1.people[1][1] = res;

    return s1.people[1][1];
}