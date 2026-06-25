#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int case_index = 1; case_index <= t; ++case_index) {
        setTestCase(case_index);

        inf.readLong(1LL, 1000000000000000000LL, "A");
        inf.readSpace();
        inf.readLong(1LL, 1000000000000000000LL, "B");
        inf.readSpace();
        inf.readInt(1, 6, "i");
        inf.readSpace();

        string c = inf.readToken("[0-9]{1,1000}", "C");
        ensuref(c[0] != '0', "C has leading zero: %s", c.c_str());
        inf.readEoln();
    }

    inf.readEof();
}
