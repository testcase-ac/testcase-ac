#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

// Helper: returns all divisors of x (including 1 and x)
vector<int> get_divisors(int x) {
    vector<int> divs;
    for (int d = 1; 1LL * d * d <= x; ++d) {
        if (x % d == 0) {
            divs.push_back(d);
            if (d != x / d) divs.push_back(x / d);
        }
    }
    return divs;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MIN = 1, T_MAX = 100000;
    const int N_MIN = 1, N_MAX = 999;
    const int X_MIN = 1, X_MAX = 1999999999;

    int T = inf.readInt(T_MIN, T_MAX, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(N_MIN, N_MAX, "n");
        inf.readEoln();

        vector<int> x = inf.readInts(n, X_MIN, X_MAX, "x_i");
        inf.readEoln();

        // Check all x_i are unique
        set<int> xset(x.begin(), x.end());
        ensuref((int)xset.size() == n, "Test case %d: Elements of S are not unique", tc);

        // Check divisor-closed property: for every x_i, all divisors d of x_i are in S
        for (int i = 0; i < n; ++i) {
            vector<int> divs = get_divisors(x[i]);
            for (int d : divs) {
                ensuref(xset.count(d), 
                    "Test case %d: S is not divisor-closed: divisor %d of x[%d]=%d is missing from S", 
                    tc, d, i+1, x[i]);
            }
        }
    }

    inf.readEof();
}
