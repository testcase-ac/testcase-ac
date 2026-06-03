#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300, "M");
    inf.readEoln();

    ensuref(n != 1 || m != 1, "start and destination must be different");

    int max_boosters = max(n, m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(1, max_boosters, "a_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
