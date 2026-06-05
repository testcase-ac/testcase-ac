#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(2, 50, "N");
        inf.readSpace();
        inf.readInt(1, 3, "K");
        inf.readEoln();

        for (int row = 0; row < n; ++row) {
            string line = inf.readToken("[.H]{2,50}", "row");
            ensuref((int)line.size() == n, "row %d has length %d, expected %d", row + 1, (int)line.size(), n);
            if (row == 0) {
                ensuref(line[0] != 'H', "top-left corner must not contain a haybale");
            }
            if (row == n - 1) {
                ensuref(line[n - 1] != 'H', "bottom-right corner must not contain a haybale");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
