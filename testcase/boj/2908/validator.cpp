#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two three-digit numbers without zero, separated by exactly one whitespace
    string A = inf.readToken("[1-9]{3}", "A");
    inf.readSpace();
    string B = inf.readToken("[1-9]{3}", "B");
    inf.readEoln();

    // They must be distinct
    ensuref(A != B, "A and B must be different, but both are %s", A.c_str());

    inf.readEof();
    return 0;
}
