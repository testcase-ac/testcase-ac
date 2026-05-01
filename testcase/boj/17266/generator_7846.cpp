#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with variety: small, medium, large (within hand-checkable range)
    int mode = rnd.next(3);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 10);
    } else if (mode == 1) {
        N = rnd.next(11, 30);
    } else {
        N = rnd.next(31, 100);
    }
    // Choose M (number of lamps) with sparse/medium/dense distribution
    int sparse_max = max(1, N / 10);
    int dense_mid = max(1, N / 2);
    int phase = rnd.next(3);
    int M;
    if (phase == 0) {
        M = rnd.next(1, sparse_max);
    } else if (phase == 1) {
        int lo = sparse_max + 1, hi = dense_mid;
        if (lo > hi) { lo = 1; hi = N; }
        M = rnd.next(lo, hi);
    } else {
        int lo = dense_mid, hi = N;
        if (lo > hi) { lo = 1; hi = N; }
        M = rnd.next(lo, hi);
    }
    // Occasionally force endpoint lamps to expose edge cases
    bool want0 = (rnd.next(10) == 0);
    bool wantN = (rnd.next(10) == 0);
    vector<int> forced;
    if (want0) forced.push_back(0);
    if (wantN) forced.push_back(N);
    // Trim forced if exceeding M
    if ((int)forced.size() > M) {
        forced.resize(M);
    }
    int rem = M - (int)forced.size();
    // Build candidate positions and pick rem random ones excluding forced
    vector<int> cand(N + 1);
    for (int i = 0; i <= N; ++i) cand[i] = i;
    shuffle(cand.begin(), cand.end());
    vector<int> pos = forced;
    for (int x : cand) {
        bool is_forced = false;
        for (int f : forced) if (f == x) { is_forced = true; break; }
        if (is_forced) continue;
        if ((int)pos.size() < M) pos.push_back(x);
        else break;
    }
    sort(pos.begin(), pos.end());
    // Output
    println(N);
    println(M);
    println(pos);
    return 0;
}
