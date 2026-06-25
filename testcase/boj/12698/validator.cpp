#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(50, 50, "N");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int r = inf.readInt(1, 15, "R");
        inf.readSpace();
        int c = inf.readInt(1, 15, "C");
        inf.readEoln();

        int startCount = 0;
        int cakeCount = 0;
        for (int row = 1; row <= r; ++row) {
            string line = inf.readLine("[.#OX]{1,15}", "row");
            ensuref((int)line.size() == c,
                    "case %d row %d has length %d, expected %d",
                    caseIndex, row, (int)line.size(), c);

            for (char ch : line) {
                if (ch == 'O') ++startCount;
                if (ch == 'X') ++cakeCount;
            }
        }

        ensuref(startCount == 1, "case %d has %d O cells", caseIndex, startCount);
        ensuref(cakeCount == 1, "case %d has %d X cells", caseIndex, cakeCount);
    }

    inf.readEof();
}
