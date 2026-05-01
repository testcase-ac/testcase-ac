#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);
    int N = 0, M = 0;
    vector<int> S; // sorted set of Minsu's cards initially

    bool shuffleS = true;       // whether to shuffle when printing
    int maxKCap = 40;           // upper cap for K by scenario

    // Helper lambda: build random subset of size M from [1..N]
    auto buildRandomSubset = [&](int N, int M) {
        vector<int> all;
        all.reserve(N);
        for (int i = 1; i <= N; ++i) all.push_back(i);
        shuffle(all.begin(), all.end());
        vector<int> res(all.begin(), all.begin() + M);
        sort(res.begin(), res.end());
        return res;
    };

    switch (scenario) {
        case 0: {
            // Very small, single move
            N = rnd.next(2, 10);
            M = rnd.next(1, min(N, 5));
            S = buildRandomSubset(N, M);
            maxKCap = 1;
            shuffleS = (rnd.next(0, 1) == 1);
            break;
        }
        case 1: {
            // Consecutive cards, K can be as large as M
            M = rnd.next(1, 10);
            N = rnd.next(M + 1, 20); // ensure N >= M+1 so we can start from 2
            S.resize(M);
            for (int i = 0; i < M; ++i) S[i] = 2 + i; // 2..M+1 (no 1)
            sort(S.begin(), S.end());
            maxKCap = M;
            shuffleS = (rnd.next(0, 1) == 1);
            break;
        }
        case 2: {
            // Medium size, completely random subset
            N = rnd.next(5, 50);
            M = rnd.next(1, min(N, 40));
            S = buildRandomSubset(N, M);
            maxKCap = M;
            shuffleS = true;
            break;
        }
        case 3: {
            // Larger N, M, near-exhausting usable cards
            N = rnd.next(50, 200);
            M = rnd.next(10, min(N, 40));
            S = buildRandomSubset(N, M);
            // With probability 1/2, ensure 1 is included to create an unusable card
            if (!S.empty() && rnd.next(0, 1) == 1) {
                bool hasOne = (S[0] == 1);
                if (!hasOne) {
                    S[0] = 1;
                    sort(S.begin(), S.end());
                }
            }
            maxKCap = M;
            shuffleS = true;
            break;
        }
        case 4: {
            // Cards biased to high values near N
            N = rnd.next(20, 200);
            M = rnd.next(1, min(20, N));
            int low = max(1, N - 2 * M); // ensure enough numbers
            vector<int> pool;
            for (int x = low; x <= N; ++x) pool.push_back(x);
            shuffle(pool.begin(), pool.end());
            S.assign(pool.begin(), pool.begin() + M);
            sort(S.begin(), S.end());
            // Avoid invalid {1} singleton set
            if (M == 1 && S[0] == 1) {
                S[0] = rnd.next(2, N);
            }
            sort(S.begin(), S.end());
            maxKCap = min(M, 15);
            shuffleS = (rnd.next(0, 1) == 1);
            break;
        }
        case 5: {
            // Special: include 1 and N and some middle values
            N = rnd.next(20, 200);
            M = rnd.next(5, min(20, N));
            // Start with required cards
            set<int> st;
            st.insert(1);
            st.insert(N);
            st.insert(2);
            st.insert(N - 1);
            while ((int)st.size() < M) {
                int x = rnd.next(1, N);
                st.insert(x);
            }
            S.assign(st.begin(), st.end());
            sort(S.begin(), S.end());
            maxKCap = M;
            shuffleS = true;
            break;
        }
    }

    M = (int)S.size();
    // Ensure N >= max(S)
    if (!S.empty()) {
        int maxS = S.back();
        if (N < maxS) N = maxS;
    }
    if (N < 2) N = 2; // safety

    // Now determine usable cards and K
    bool hasOne = (!S.empty() && S[0] == 1);
    int usable = M - (hasOne ? 1 : 0); // cards with value > 1
    // Avoid impossible case M==1 and S[0]==1
    if (usable <= 0) {
        // Fix by changing the single card to >1
        S[0] = 2;
        sort(S.begin(), S.end());
        hasOne = (S[0] == 1);
        usable = M - (hasOne ? 1 : 0);
    }

    int maxK = min(usable, maxKCap);
    int minK = 1;

    if (scenario == 3) {
        // Make K close to maximum usable
        if (maxK >= 3) {
            int delta = rnd.next(0, 2); // 0,1,2
            minK = max(1, maxK - delta);
        }
    }

    if (minK > maxK) minK = maxK;
    int K = rnd.next(minK, maxK);

    // Generate Cheolsu's moves and implied Minsu responses
    vector<int> available = S; // always kept sorted ascending
    vector<int> queries;
    queries.reserve(K);

    for (int step = 0; step < K; ++step) {
        // Determine index range of usable 'b' (Minsu's card)
        bool curHasOne = (!available.empty() && available[0] == 1);
        int startIdx = curHasOne ? 1 : 0; // we never choose value 1 as response
        int usableRemaining = (int)available.size() - (curHasOne ? 1 : 0);

        // Sanity: there must be enough cards left
        if (usableRemaining <= 0) {
            // Should not happen due to K<=usable logic
            startIdx = 0;
        }

        int idx;
        int choiceType = rnd.next(0, 2);
        if (choiceType == 0) {
            // smallest usable
            idx = startIdx;
        } else if (choiceType == 1) {
            // largest usable
            idx = (int)available.size() - 1;
        } else {
            // random usable
            idx = startIdx + rnd.next(0, usableRemaining - 1);
        }

        int b = available[idx];
        int prevVal = (idx > 0 ? available[idx - 1] : 0);
        int lo = max(prevVal, 1);
        int hi = b - 1;
        if (hi < lo) hi = lo; // safety, though should not occur except illegal b=1

        int a;
        int choiceAType = rnd.next(0, 2);
        if (choiceAType == 0) a = lo;
        else if (choiceAType == 1) a = hi;
        else a = rnd.next(lo, hi);

        queries.push_back(a);

        // Remove used card b from available
        available.erase(available.begin() + idx);
    }

    // Prepare S for printing (possibly shuffled)
    vector<int> S_print = S;
    if (shuffleS) {
        shuffle(S_print.begin(), S_print.end());
    }

    // Output
    println(N, M, K);
    println(S_print);
    println(queries);

    return 0;
}
