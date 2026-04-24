#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    int n = inf.readInt();
    string s = inf.readToken();
    int N = 2 * n - 1;
    if ((int)s.size() != N) {
        // Input file is malformed
        inf.quitf(_fail, "input string length mismatch");
    }
    // Read participant's answer x
    int x = ouf.readInt(0, N, "x");
    // No extra tokens
    ouf.skipBlanks();
    if (!ouf.eof())
        ouf.quitf(_wa, "extra data after reading x");

    // Build prefix sums of white wines
    vector<int> w(N+1, 0);
    for (int i = 1; i <= N; i++) {
        w[i] = w[i-1] + (s[i-1] == 'W');
    }
    // We'll count number of intervals [l..r] of length >= n with exactly x whites.
    // For each r from n..N, number of l such that 1 <= l <= r-n+1 and w[r] - w[l-1] == x
    // is equal to count of k in [0..r-n] with w[k] == w[r] - x.
    // We maintain a frequency table of prefix sums w[k].
    int maxW = N; // prefix sums go from 0..N
    vector<int> freq(maxW+1, 0);
    long long cnt = 0;
    // Initially for r = n, valid k is only 0
    freq[w[0]]++;
    for (int r = n; r <= N; r++) {
        if (r > n) {
            // include k = r-n into freq
            int k = r - n;
            freq[w[k]]++;
        }
        int need = w[r] - x;
        if (0 <= need && need <= maxW) {
            cnt += freq[need];
        }
        // early exit if we already found enough
        if (cnt >= n) break;
    }
    if (cnt >= n) {
        quitf(_ok, "valid x = %d: found %lld suitable intervals", x, cnt);
    } else {
        quitf(_wa, "invalid x = %d: only %lld intervals of length >= %d have %d whites, need >= %d",
              x, cnt, n, x, n);
    }
    return 0;
}
