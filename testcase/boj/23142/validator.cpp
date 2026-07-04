#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "n");
    inf.readSpace();
    int m = inf.readInt(1, 300, "m");
    inf.readEoln();

    int total = n * m;
    vector<bool> seen(total + 1, false);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }

            int value = inf.readInt(1, total, "a_ij");
            ensuref(!seen[value],
                    "combat value %d appears more than once, latest position (%d, %d)",
                    value, i, j);
            seen[value] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
