#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 999, "N");
    inf.readEoln();
    ensuref(n % 2 == 1, "N must be odd: %d", n);

    vector<int> p = inf.readInts(n, 1, 999, "p_i");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        ensuref(p[i] % 2 == 1, "p_%d must be odd: %d", i + 1, p[i]);
    }

    inf.readEof();
    return 0;
}
