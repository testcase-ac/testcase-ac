#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000000000, "M");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, m - 1, "A");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        ensuref(gcd(a[i], m) == 1,
                "A[%d]=%d is not coprime with M=%d", i + 1, a[i], m);
    }

    inf.readEof();
}
