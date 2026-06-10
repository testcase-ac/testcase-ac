#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int h = inf.readInt(1, n, "h_i");
        ensuref(!seen[h], "height %d appears more than once", h);
        seen[h] = 1;

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
