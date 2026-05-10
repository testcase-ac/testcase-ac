#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n / 2, "k");
    inf.readEoln();

    // Read n positions, one per line
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        s[i] = inf.readInt(0, 1000000000, "s_i");
        inf.readEoln();
    }

    // Check strictly increasing order and uniqueness
    for (int i = 1; i < n; ++i) {
        ensuref(s[i] > s[i - 1], "s[%d]=%d is not strictly greater than s[%d]=%d", i, s[i], i - 1, s[i - 1]);
    }

    inf.readEof();
}
