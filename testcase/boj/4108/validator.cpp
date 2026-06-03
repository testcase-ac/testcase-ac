#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    int totalCells = 0;

    while (true) {
        int r = inf.readInt(0, 100, "R");
        inf.readSpace();
        int c = inf.readInt(0, 100, "C");
        inf.readEoln();

        if (r == 0 && c == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);

        ensuref(r >= 1 && c >= 1, "case %d has invalid dimensions: %d %d", caseCount, r, c);

        totalCells += r * c;
        // CHECK: the statement does not bound the number of test cases; cap total board cells to keep inputs practical.
        ensuref(totalCells <= 10000000, "total board cells exceed practical cap: %d", totalCells);

        string pattern = "[*.]{" + to_string(c) + "," + to_string(c) + "}";
        for (int i = 0; i < r; ++i) {
            inf.readLine(pattern, "row");
        }
    }

    // CHECK: reject a vacuous input with only the terminator.
    ensuref(caseCount >= 1, "at least one test case is required");

    inf.readEof();
}
