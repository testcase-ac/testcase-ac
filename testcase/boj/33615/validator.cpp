#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    int totalLength = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string n = inf.readToken("[15]{3,500000}", "N");
        inf.readEoln();

        totalLength += static_cast<int>(n.size());
        ensuref(totalLength <= 500000,
                "sum of lengths exceeds 500000 after testcase %d: %d",
                tc,
                totalLength);
    }

    inf.readEof();
}
