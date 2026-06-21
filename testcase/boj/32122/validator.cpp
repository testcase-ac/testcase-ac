#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    ensuref(n % 2 == 0, "N must be even: %d", n);
    inf.readEoln();

    vector<bool> seen(n * n + 1, false);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int value = inf.readInt(1, n * n, "a_ij");
            ensuref(!seen[value], "duplicate grid value at row %d column %d: %d",
                    i + 1, j + 1, value);
            seen[value] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
