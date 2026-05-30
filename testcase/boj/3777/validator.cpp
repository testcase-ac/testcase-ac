#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    bool hasInput = false;
    while (!inf.eof()) {
        // CHECK: The statement has no explicit number-of-lines limit.
        ensuref(lineCount < 100000, "too many input lines");
        inf.readInt(1, 1000, "n");
        inf.readEoln();
        ++lineCount;
        hasInput = true;
    }

    ensuref(hasInput, "input must contain at least one value");
    inf.readEof();
}
