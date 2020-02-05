#include <string>
using namespace std;
#include "switchName.idl"

void switchName(Person &orig) {
    string temp = orig.firstname;
    orig.firstname = orig.lastname;
    orig.lastname = temp;
}