#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "k");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 2000, "a_i");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(a[i - 1] <= a[i],
                "a must be nondecreasing, but a[%d]=%d > a[%d]=%d",
                i,
                a[i - 1],
                i + 1,
                a[i]);
    }

    inf.readEof();
}
