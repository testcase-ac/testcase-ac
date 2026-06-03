#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    bool hasNonZeroLeadingDigit = false;

    while (!inf.eof()) {
        ++lineCount;
        ensuref(lineCount <= 100, "number of lines must not exceed 100");

        string line = inf.readLine("[0-9]{1,100}", "part");
        if (line[0] != '0') {
            hasNonZeroLeadingDigit = true;
        }
    }

    ensuref(lineCount >= 1, "input must contain at least one line");
    ensuref(hasNonZeroLeadingDigit, "at least one line must start with a nonzero digit");

    inf.readEof();
    return 0;
}
