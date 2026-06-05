#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1500, "N");
    inf.readEoln();

    bool hasGomgom = false;
    for (int row = 1; row <= n; ++row) {
        string line = inf.readLine("[G\\.]{1,1500}", "row");
        ensuref((int)line.size() == n, "row %d length is %d, expected %d", row, (int)line.size(), n);
        for (char cell : line) {
            if (cell == 'G') {
                hasGomgom = true;
            }
        }
    }

    ensuref(hasGomgom, "at least one G is required");
    inf.readEof();
}
