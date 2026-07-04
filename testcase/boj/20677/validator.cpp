#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    int startCount = 0;
    int endCount = 0;
    for (int i = 0; i < m; ++i) {
        string row = inf.readLine("[*#.SE]{1,500}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), n);

        for (char cell : row) {
            if (cell == 'S') {
                ++startCount;
            } else if (cell == 'E') {
                ++endCount;
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one S, found %d", startCount);
    ensuref(endCount == 1, "expected exactly one E, found %d", endCount);

    inf.readEof();
}
