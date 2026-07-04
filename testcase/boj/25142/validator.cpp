#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    int startCount = 0;
    int finishCount = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[SF.#]{1,1000}", "row");
        ensuref(static_cast<int>(row.size()) == m,
                "row %d has length %d, expected %d",
                i + 1,
                static_cast<int>(row.size()),
                m);

        for (char cell : row) {
            if (cell == 'S') {
                ++startCount;
            } else if (cell == 'F') {
                ++finishCount;
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one S, found %d", startCount);
    ensuref(finishCount == 1, "expected exactly one F, found %d", finishCount);

    inf.readEof();
}
