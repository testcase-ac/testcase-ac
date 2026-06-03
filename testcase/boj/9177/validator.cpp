#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string a = inf.readToken("[A-Za-z]{1,200}", "a");
        inf.readSpace();
        string b = inf.readToken("[A-Za-z]{1,200}", "b");
        inf.readSpace();
        string c = inf.readToken("[A-Za-z]{2,400}", "c");
        inf.readEoln();

        ensuref(c.size() == a.size() + b.size(),
                "third word length must be sum of first two lengths: %d != %d + %d",
                static_cast<int>(c.size()), static_cast<int>(a.size()),
                static_cast<int>(b.size()));
    }

    inf.readEof();
}
