#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    vector<char> seen(1000001, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int value = inf.readInt(0, 1000000, "a_ij");
            ensuref(!seen[value],
                    "duplicate grid value at row %d column %d: %d",
                    i + 1,
                    j + 1,
                    value);
            seen[value] = 1;
        }
        inf.readEoln();
    }

    inf.readEof();
}
