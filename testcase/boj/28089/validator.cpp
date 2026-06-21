#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 2000000;
    int n = inf.readInt(3, maxN, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    inf.readLong(0LL, 1000000000000000000LL, "K");
    inf.readEoln();

    vector<bool> seen(n, false);
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(0, n - 1, "x_i");
        inf.readEoln();
        ensuref(!seen[x], "duplicate initial greeter at line %d: %d", i + 2, x);
        seen[x] = true;
    }

    inf.readEof();
}
