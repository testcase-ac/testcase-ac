#include "testlib.h"

#include <limits>
#include <set>
#include <vector>
using namespace std;

static bool countFitsSigned64(const vector<int>& a, int k) {
    const unsigned long long limit = static_cast<unsigned long long>(numeric_limits<long long>::max());
    int n = static_cast<int>(a.size());
    vector<unsigned long long> dp(n, 1);

    for (int len = 2; len <= k; ++len) {
        vector<unsigned long long> next(n, 0);
        for (int i = 0; i < n; ++i) {
            unsigned long long total = 0;
            for (int j = 0; j < i; ++j) {
                if (a[j] < a[i]) {
                    if (total > limit - dp[j]) {
                        return false;
                    }
                    total += dp[j];
                }
            }
            next[i] = total;
        }
        dp.swap(next);
    }

    unsigned long long total = 0;
    for (unsigned long long ways : dp) {
        if (total > limit - ways) {
            return false;
        }
        total += ways;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int tc = 1;; ++tc) {
        int n = inf.readInt(0, 100, "n");
        inf.readSpace();
        int k = inf.readInt(0, 100, "k");
        inf.readEoln();

        if (n == 0 && k == 0) {
            break;
        }

        setTestCase(tc);
        ensuref(1 <= k && k <= n, "expected 1 <= k <= n, got n=%d k=%d", n, k);

        vector<int> a = inf.readInts(n, -10000, 10000, "a_i");
        inf.readEoln();

        set<int> seen;
        for (int i = 0; i < n; ++i) {
            ensuref(seen.insert(a[i]).second, "duplicate sequence value at index %d: %d", i + 1, a[i]);
        }
        ensuref(countFitsSigned64(a, k), "answer does not fit in signed 64-bit integer");
    }

    inf.readEof();
}
