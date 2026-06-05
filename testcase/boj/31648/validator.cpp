#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        setTestCase(caseNum);

        string s = inf.readToken("[0-9]{1,100000}", "S");
        inf.readEoln();

        ensuref(s[0] != '0', "S must be positive and must not have leading zeros");
    }

    inf.readEof();
    return 0;
}
