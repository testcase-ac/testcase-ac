#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    vector<bool> seen(n * m + 1, false);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int value = inf.readInt(1, n * m, "a_ij");
            ensuref(!seen[value], "duplicate table value %d at row %d column %d", value, i, j);
            seen[value] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
