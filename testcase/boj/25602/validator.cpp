#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5, "N");
    inf.readSpace();
    int k = inf.readInt(1, 4, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 8, "A_i");
    inf.readEoln();

    int totalCans = accumulate(a.begin(), a.end(), 0);
    ensuref(totalCans >= 2 * k, "sum of A_i must be at least 2*K, got %d < %d", totalCans, 2 * k);

    for (int day = 1; day <= k; ++day) {
        inf.readInts(n, 1, 100, "R_i_j");
        inf.readEoln();
    }

    for (int day = 1; day <= k; ++day) {
        inf.readInts(n, 1, 100, "M_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
