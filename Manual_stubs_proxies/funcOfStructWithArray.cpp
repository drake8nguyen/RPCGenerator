#include <string>
using namespace std;
#include "funcOfStructWithArray.idl"

Person operation1(StructWithArrays s) {
    int average = 0;
    for (int i = 0; i < 2; ++i) 
        average += s.people[i].age;
    return {"Noah", "Mendelsohn", average/2};
}


