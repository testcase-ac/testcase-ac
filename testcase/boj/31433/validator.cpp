#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string x = inf.readToken("[KSA]{1,500000}", "X");
    inf.readEoln();
    ensuref(!x.empty(), "X must be non-empty");
    inf.readEof();
}
