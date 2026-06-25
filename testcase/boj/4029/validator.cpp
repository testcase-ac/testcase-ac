#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (true) {
        int b = inf.readInt(0, 500, "b");
        inf.readSpace();
        int c = inf.readInt(0, 2500, "c");
        inf.readEoln();

        if (b == 0 && c == 0) {
            break;
        }
        ensuref(b >= 1, "case %d has b = %d, expected at least 1", caseIndex, b);
        ensuref(c >= 1, "case %d has c = %d, expected at least 1", caseIndex, c);

        setTestCase(caseIndex);
        for (int i = 0; i < b; ++i) {
            vector<int> seen(c, 0);
            for (int j = 0; j < c; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                int candidate = inf.readInt(0, c - 1, "candidate");
                ensuref(!seen[candidate],
                        "case %d ballot %d contains duplicate candidate %d",
                        caseIndex, i + 1, candidate);
                seen[candidate] = 1;
            }
            inf.readEoln();
        }

        ++caseIndex;
    }

    inf.readEof();
}
