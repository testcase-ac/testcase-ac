#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        b[i] = inf.readLong(0LL, 2147483647LL, "b_i");
    }
    inf.readEoln();
    inf.readEof();

    vector<int> remaining(n);
    iota(remaining.begin(), remaining.end(), 1);
    vector<bool> used(n + 1, false);

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            b[j] ^= remaining[j];
        }

        long long value = b[i];
        ensuref(1 <= value && value <= n,
                "reconstructed p_%d is out of range: %lld", i + 1, value);
        ensuref(!used[value], "reconstructed value is duplicated: %lld", value);

        used[value] = true;
        auto it = find(remaining.begin(), remaining.end(), static_cast<int>(value));
        ensuref(it != remaining.end(), "reconstructed value is not remaining: %lld", value);
        remaining.erase(it);
    }
}
