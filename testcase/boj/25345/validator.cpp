#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "A_%d is duplicated: %lld", i + 1, a[i]);
    }

    inf.readEof();
}
