#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readEoln();

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            inf.readSpace();
        }
        parent[i] = inf.readInt(1, i - 1, "p_i");
    }
    inf.readEoln();

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        a[i] = inf.readLong(1LL, 1000000000LL, "A_i");
    }
    inf.readEoln();

    for (int i = 2; i <= n; ++i) {
        ensuref(a[i] <= a[parent[i]],
                "A_%d=%lld exceeds parent A_%d=%lld",
                i,
                a[i],
                parent[i],
                a[parent[i]]);
    }

    inf.readEof();
}
