#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_N = 100000;
    constexpr long long MAX_COST = 1000000000LL;

    int n = inf.readInt(3, MAX_N, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    int previousCity = 0;
    for (int i = 1; i <= m; ++i) {
        int c = inf.readInt(1, n, "c_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_COST, "a_i");
        inf.readEoln();

        ensuref(previousCity < c,
                "plant city values must be strictly increasing: c_%d=%d after %d",
                i,
                c,
                previousCity);
        previousCity = c;
    }

    inf.readLongs(n, 1LL, MAX_COST, "b_i");
    inf.readEoln();
    inf.readEof();
}
