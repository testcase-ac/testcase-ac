#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string x = inf.readToken("[0-9]{3,100000}", "x");
    ensuref(x[0] != '0', "x must be a canonical positive integer without leading zero");
    inf.readEoln();
    inf.readEof();
}
