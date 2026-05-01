#include "testlib.h"
using namespace std;

// Greedy maximum reachable position after K moves (always take the move that increases position the most)
long long maxReachAfterK(int K) {
    long long pos = 0;
    for (int step = 0; step < K; ++step) {
        long long inc = (pos / 2 > 1 ? pos / 2 : 1); // max(1, floor(pos/2))
        pos += inc;
    }
    return pos;
}

// DP: reachable positions in exactly K moves from 0, limited to [0..Nmax]
vector<char> reachableStates(int K, int Nmax) {
    vector<char> cur(Nmax + 1, 0), nxt(Nmax + 1, 0);
    cur[0] = 1;
    for (int step = 0; step < K; ++step) {
        fill(nxt.begin(), nxt.end(), 0);
        for (int i = 0; i <= Nmax; ++i) {
            if (!cur[i]) continue;
            int p1 = i + 1;
            if (p1 <= Nmax) nxt[p1] = 1;
            int p2 = i + i / 2;
            if (p2 <= Nmax) nxt[p2] = 1;
        }
        cur.swap(nxt);
    }
    return cur;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int KMAX = 20; // keep K small so validator's bounds are never exceeded

    int N = 1, K = 1;
    int scenario = rnd.next(1, 7);

    if (scenario == 1) {
        // Small reachable case via exact DP
        while (true) {
            K = rnd.next(1, KMAX);
            int Nmax = max(K, rnd.next(3, 40));
            vector<char> reach = reachableStates(K, Nmax);
            vector<int> cand;
            for (int i = 1; i <= Nmax; ++i)
                if (reach[i]) cand.push_back(i);
            if (cand.empty()) continue;
            N = rnd.any(cand);
            break;
        }
    } else if (scenario == 2) {
        // Small unreachable case via exact DP
        while (true) {
            K = rnd.next(1, KMAX);
            int Nmax = max(K, rnd.next(3, 40));
            vector<char> reach = reachableStates(K, Nmax);
            vector<int> cand;
            for (int i = 1; i <= Nmax; ++i)
                if (!reach[i]) cand.push_back(i);
            if (cand.empty()) continue;
            N = rnd.any(cand);
            break;
        }
    } else if (scenario == 3) {
        // Reachable via an explicit random sequence of operations (possibly larger N)
        K = rnd.next(1, KMAX);
        int pos = 0;
        for (int step = 0; step < K; ++step) {
            bool useTeleport = false;
            if (pos >= 2) {
                useTeleport = (rnd.next(0, 99) < 60);
            }
            int npos = useTeleport ? (pos + pos / 2) : (pos + 1);
            pos = npos;
        }
        if (pos <= 0) {
            // Fallback: simple walk
            N = K;
        } else {
            N = pos;
        }
    } else if (scenario == 4) {
        // Unreachable because even optimal play can't reach N in K moves (medium N)
        K = rnd.next(1, KMAX);
        long long f = maxReachAfterK(K); // maximum reachable in K moves
        long long lo = f + 1;
        long long hi = min(1000000LL, f + (long long)rnd.next(1, 100000));
        if (lo > 1000000LL) lo = 1000000LL;
        if (hi < lo) hi = lo;
        N = (int)rnd.next((int)lo, (int)hi);
    } else if (scenario == 5) {
        // Edge cases around N = 1 or 2 with varied K
        if (rnd.next(0, 1) == 0) {
            // N = 1, always reachable for any K >= 1
            N = 1;
            K = rnd.next(1, KMAX);
        } else {
            // N = 2, K = 1 unreachable, K >= 2 reachable
            N = 2;
            if (rnd.next(0, 1) == 0) {
                K = 1; // unreachable
            } else {
                K = rnd.next(2, KMAX); // reachable
            }
        }
    } else if (scenario == 6) {
        // Large N (near upper bound), guaranteed unreachable
        K = rnd.next(1, KMAX);
        long long f = maxReachAfterK(K);
        int minN = (int)max( (long long)500000, f + 1 );
        if (minN > 1000000) minN = 1000000;
        N = rnd.next(minN, 1000000);
    } else if (scenario == 7) {
        // Simple walk-only reachable or unreachable small/medium cases
        if (rnd.next(0, 1) == 0) {
            // Walk-only reachable: N = K
            K = rnd.next(1, KMAX);
            N = K;
        } else {
            // Slightly above max reachable for this K
            K = rnd.next(1, KMAX);
            long long f = maxReachAfterK(K);
            int lo = (int)(f + 1);
            int hi = (int)min(1000000LL, f + (long long)rnd.next(1, 1000));
            if (lo > hi) lo = hi;
            N = rnd.next(lo, hi);
        }
    }

    // Ensure within problem constraints
    if (N < 1) N = 1;
    if (K < 1) K = 1;
    if (N > 1000000) N = 1000000;
    if (K > 1000000) K = 1000000;

    println(N, K);
    return 0;
}
