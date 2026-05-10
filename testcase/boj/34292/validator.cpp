#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n and l
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int l = inf.readInt(2, 100000000, "l");
    inf.readEoln();

    // Second line: d_1 ... d_n
    vector<int> d(n);
    d[0] = inf.readInt(1, l - 1, "d_1");
    for (int i = 1; i < n; ++i) {
        inf.readSpace();
        d[i] = inf.readInt(1, l - 1, format("d_%d", i + 1).c_str());
        ensuref(d[i] > d[i - 1], "d_i must be strictly increasing: d[%d]=%d, d[%d]=%d", i, d[i], i-1, d[i-1]);
    }
    inf.readEoln();

    // Check d_1 > 0 and d_n < l
    ensuref(d[0] > 0, "d_1 must be > 0, got %d", d[0]);
    ensuref(d[n-1] < l, "d_n must be < l, got d_n=%d, l=%d", d[n-1], l);

    // Third line: w_1 ... w_n
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(0, 100000000, format("w_%d", i + 1).c_str());
    }
    inf.readEoln();

    // Fourth line: v
    inf.readInt(1, 100000000, "v");
    inf.readEoln();

    inf.readEof();
}
