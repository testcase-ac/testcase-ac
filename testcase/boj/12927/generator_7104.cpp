#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

static vector<int> primesUpTo(int n) {
    vector<int> primes;
    if (n < 2) return primes;
    vector<bool> isP(n + 1, true);
    isP[0] = isP[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (isP[i]) {
            for (int j = i * i; j <= n; j += i) isP[j] = false;
        }
    }
    for (int i = 2; i <= n; ++i) if (isP[i]) primes.push_back(i);
    return primes;
}

static string fromPressSet(int N, const vector<int>& S) {
    vector<int> st(N + 1, 0);
    for (int i : S) {
        for (int j = i; j <= N; j += i) st[j] ^= 1;
    }
    string s;
    s.reserve(N);
    for (int i = 1; i <= N; ++i) s.push_back(st[i] ? 'Y' : 'N');
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Limit size to keep inputs hand-checkable and under 500 chars.
    auto smallN = [&]() { return rnd.next(1, 30); };
    auto mediumN = [&]() { return rnd.next(31, 120); };
    auto anyN = [&]() { return rnd.next(1, 120); };

    int mode = rnd.next(0, 10);

    string out;
    if (mode == 0) {
        // Pure random with biased probability
        int N = (rnd.next(0, 3) ? smallN() : mediumN());
        vector<double> probs = {0.05, 0.2, 0.5, 0.8, 0.95};
        double p = rnd.any(probs);
        out.reserve(N);
        for (int i = 0; i < N; ++i) out.push_back(rnd.next() < p ? 'Y' : 'N');
    } else if (mode == 1) {
        // Alternating pattern starting from random char
        int N = rnd.next(10, 60);
        char start = rnd.any(string("YN"));
        out.reserve(N);
        for (int i = 0; i < N; ++i) {
            out.push_back((i % 2 == 0) ? start : (start == 'Y' ? 'N' : 'Y'));
        }
    } else if (mode == 2) {
        // All Ys
        int N = anyN();
        out.assign(N, 'Y');
    } else if (mode == 3) {
        // All Ns
        int N = anyN();
        out.assign(N, 'N');
    } else if (mode == 4) {
        // Primes ON
        int N = rnd.next(10, 120);
        vector<int> primes = primesUpTo(N);
        vector<char> st(N + 1, 'N');
        for (int p : primes) st[p] = 'Y';
        out.reserve(N);
        for (int i = 1; i <= N; ++i) out.push_back(st[i]);
    } else if (mode == 5) {
        // Perfect squares ON
        int N = rnd.next(20, 120);
        out.reserve(N);
        for (int i = 1; i <= N; ++i) {
            int r = (int)floor(sqrt((double)i));
            out.push_back(r * r == i ? 'Y' : 'N');
        }
    } else if (mode == 6) {
        // State derived by pressing all prime switches
        int N = rnd.next(10, 120);
        vector<int> primes = primesUpTo(N);
        out = fromPressSet(N, primes);
    } else if (mode == 7) {
        // State derived by pressing a random subset (20%-50% density)
        int N = rnd.next(25, 120);
        double p = rnd.next(0, 1) ? rnd.next(0.2, 0.35) : rnd.next(0.35, 0.5);
        vector<int> S;
        for (int i = 1; i <= N; ++i) if (rnd.next() < p) S.push_back(i);
        if (S.empty()) S.push_back(rnd.next(1, N));
        out = fromPressSet(N, S);
    } else if (mode == 8) {
        // State derived by pressing only high-index switches
        int N = rnd.next(15, 120);
        int k = rnd.next(1, min(6, N));
        vector<int> cand;
        for (int i = max(1, N - k + 1); i <= N; ++i) cand.push_back(i);
        vector<int> S;
        for (int i : cand) if (rnd.next(0, 1)) S.push_back(i);
        if (S.empty()) S.push_back(rnd.any(cand));
        out = fromPressSet(N, S);
    } else if (mode == 9) {
        // State derived by pressing only small-index switches
        int N = rnd.next(15, 120);
        int T = rnd.next(2, min(10, N));
        vector<int> S;
        for (int i = 1; i <= T; ++i) if (rnd.next(0, 1)) S.push_back(i);
        if (S.empty()) S.push_back(rnd.next(1, T));
        out = fromPressSet(N, S);
    } else {
        // Pick one of the provided examples
        vector<string> samples = {
            "YYYYYY",
            "YNYNYNYNY",
            "NNNNNNNNNN",
            "YYYNYYYNYYYNYYNYYYYN"
        };
        out = rnd.any(samples);
    }

    println(out);
    return 0;
}
