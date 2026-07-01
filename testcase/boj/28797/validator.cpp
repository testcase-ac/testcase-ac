#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[0-2]\\.[0-9]{6}", "A");
    if (a[0] == '2') {
        ensuref(a == "2.000000", "A must not exceed 2.000000, found %s", a.c_str());
    }
    inf.readEoln();
    inf.readEof();
}
