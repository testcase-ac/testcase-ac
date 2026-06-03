#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500, "N");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, -1000000000000000LL, 1000000000000000LL, "a_i");
    inf.readEoln();
    inf.readEof();

    vector<__int128_t> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + static_cast<__int128_t>(a[i]);
    }

    set<__int128_t> sums;
    for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
            __int128_t sum = prefix[r] - prefix[l];
            ensuref(sums.insert(sum).second,
                    "duplicate contiguous subarray sum for interval [%d, %d]",
                    l + 1,
                    r);
        }
    }
}
