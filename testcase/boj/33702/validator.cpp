#include "testlib.h"

using namespace std;

// Map button number (1..9) to (row, col) on 3x3 grid
pair<int,int> posOf(int v) {
    int r = (v - 1) / 3;
    int c = (v - 1) % 3;
    return {r, c};
}

// Check that a permutation of 1..9 is a valid password path
bool isValidPath(const vector<int>& p) {
    if ((int)p.size() != 9) return false;
    // must contain 1..9 exactly once
    bool used[10] = {false};
    for (int x : p) {
        if (x < 1 || x > 9) return false;
        if (used[x]) return false;
        used[x] = true;
    }
    for (int v = 1; v <= 9; ++v)
        if (!used[v]) return false;

    for (int i = 1; i < 9; ++i) {
        auto [r1, c1] = posOf(p[i - 1]);
        auto [r2, c2] = posOf(p[i]);
        int dr = abs(r1 - r2);
        int dc = abs(c1 - c2);
        // must be adjacent and not diagonal
        if (!((dr == 1 && dc == 0) || (dr == 0 && dc == 1)))
            return false;
    }
    return true;
}

// Precompute answer for each starting button K
long long precomputeAnswer(int K) {
    vector<int> p(9);
    for (int i = 0; i < 9; ++i) p[i] = i + 1;
    long long cnt = 0;
    do {
        if (p[0] != K) continue;
        if (isValidPath(p)) ++cnt;
    } while (next_permutation(p.begin(), p.end()));
    return cnt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer K, canonical decimal, 1..9
    int K = inf.readInt(1, 9, "K");
    inf.readEoln();

    // Problem guarantees that an answer always exists (possibly 0) and fits
    // in standard integer output; we verify by computing it.
    long long ans = precomputeAnswer(K);
    // Sanity bound: answer must be between 0 and 9! = 362880
    ensuref(0 <= ans && ans <= 362880LL,
            "Computed number of passwords for K=%d out of reasonable bounds: %lld",
            K, ans);

    inf.readEof();
}
