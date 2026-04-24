#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for period T
    int T = rnd.next(5, 20);

    // Hyper-parameter for number of dangerous turns N (1 <= N <= min(T,5))
    int maxN = min(T, 5);
    int t_param = rnd.next(-1, 1);
    int N = rnd.wnext(maxN + 1, t_param); // yields in [0, maxN]
    if (N < 1) N = 1;
    if (N > maxN) N = maxN;

    // Hyper-parameter for line length L
    int L = rnd.next(1, 20);

    // Hyper-parameter for number of permanent platforms K (2 <= K <= min(L+1,5))
    int maxK = min(L + 1, 5);
    t_param = rnd.next(-1, 1);
    int K = rnd.wnext(maxK + 1, t_param); // yields in [0, maxK]
    if (K < 2) K = 2;
    if (K > maxK) K = maxK;

    // Generate N distinct dangerous turns in [0, T-1]
    vector<int> danger;
    danger.reserve(N);
    {
        set<int> used;
        while ((int)danger.size() < N) {
            int x = rnd.next(0, T - 1);
            if (used.insert(x).second) {
                danger.push_back(x);
            }
        }
        sort(danger.begin(), danger.end());
    }

    // Generate K distinct permanent platform positions in [0, L], include 0 and L
    vector<long long> perm;
    perm.reserve(K);
    {
        set<long long> used;
        // always include endpoints
        used.insert(0);
        used.insert(L);
        vector<long long> mids;
        while ((int)mids.size() < K - 2) {
            if (L <= 1) break;
            long long x = rnd.next(1, L - 1);
            if (used.insert(x).second) {
                mids.push_back(x);
            }
        }
        sort(mids.begin(), mids.end());
        perm.push_back(0);
        for (auto x : mids) perm.push_back(x);
        perm.push_back(L);
    }

    // Output
    println(T, N);
    println(L, K);
    println(danger);
    println(perm);

    return 0;
}
