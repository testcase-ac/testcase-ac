#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[1-9]{1,10000}", "N");
    ensuref(!n.empty(), "N must be non-empty");
    inf.readEoln();
    inf.readEof();
}
