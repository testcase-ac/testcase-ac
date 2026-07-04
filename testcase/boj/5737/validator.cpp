#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    int totalCells = 0;

    while (true) {
        int r = inf.readInt(0, 100, "R");
        inf.readSpace();
        int c = inf.readInt(0, 100, "C");
        inf.readEoln();

        if (r == 0 && c == 0) {
            break;
        }

        ensuref(r >= 1 && c >= 1, "R and C must both be positive or both be zero");

        ++testCases;
        // CHECK: The statement does not bound the number of test cases, so cap
        // the aggregate grid area to keep validation inputs practical.
        ensuref(testCases <= 100000, "too many test cases: %d", testCases);
        totalCells += r * c;
        ensuref(totalCells <= 1000000, "total grid area too large: %d", totalCells);

        string rowPattern = "[.*I]{" + to_string(c) + "," + to_string(c) + "}";
        for (int i = 0; i < r; ++i) {
            inf.readLine(rowPattern, "row");
        }
    }

    inf.readEof();
}
