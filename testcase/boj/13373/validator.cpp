#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int n = inf.readInt(0, 10000, "n");
        inf.readSpace();
        int k = inf.readInt(0, 10000, "k");
        inf.readEoln();

        vector<long long> a;
        a.reserve(k);
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            long long v = inf.readLong(0LL, 1000000LL, "arr_i");
            if (i + 1 < k) inf.readSpace();
            a.push_back(v);
            sum += v;
        }
        inf.readEoln();

        ensuref((int)a.size() == k, "Expected %d array elements, got %d", k, (int)a.size());

        // Compute minimal possible return of getMin to check any promise like "answer always exists".
        // Rearranging to minimize return means subtracting larger elements first:
        sort(a.begin(), a.end(), greater<long long>());
        long long cur = n;
        for (int i = 0; i < k; ++i) {
            cur -= a[i];
            if (cur <= 0) break;
        }
        long long answer = cur;
        // No explicit bound on answer is stated besides being an integer; no extra ensure needed.
        // But we at least ensure no overflow happened relative to sum bounds:
        // n in [0,1e4], k<=1e4, each a[i]<=1e6 => sum<=1e10, fits in signed 64-bit.

        (void)answer; // suppress unused variable warning if compiled with -Wall
    }

    inf.readEof();
}
