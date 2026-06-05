#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int tMax = inf.readInt(1, 1000000, "T_max");
    inf.readEoln();

    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        d[i] = inf.readInt(1, 100000, "d_i");
        inf.readEoln();
    }

    ensuref(*max_element(d.begin(), d.end()) <= tMax,
            "K=N must finish in time, but max duration is %d and T_max is %d",
            *max_element(d.begin(), d.end()), tMax);

    inf.readEof();
}
