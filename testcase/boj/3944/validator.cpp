#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int b = inf.readInt(2, 10, "B");
        inf.readSpace();

        string d = inf.readToken("[0-9]{1,10000000}", "D");
        ensuref(d == "0" || d[0] != '0', "D has leading zero");

        for (int i = 0; i < int(d.size()); ++i) {
            int digit = d[i] - '0';
            ensuref(digit < b, "D[%d] is %d, which is not a valid base-%d digit", i + 1, digit, b);
        }

        inf.readEoln();
    }

    inf.readEof();
}
