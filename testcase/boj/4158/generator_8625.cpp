#include "testlib.h"
using namespace std;

struct NMConfig {
    int N, M, C; // sizes of A, B, and intersection
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_TOTAL = 35; // max total N+M over all test cases (excluding sentinel)

    vector<int> modes = {0, 1, 2, 3, 4, 5, 6};
    shuffle(modes.begin(), modes.end());

    int totalCDs = 0;
    bool producedAny = false;

    for (int mode : modes) {
        int remaining = MAX_TOTAL - totalCDs;
        if (remaining <= 0) break;

        vector<NMConfig> cand;

        // Prepare candidate (N, M, C) configurations for this mode
        switch (mode) {
            case 0: // empty intersection
                cand.push_back({1, 1, 0});
                cand.push_back({2, 3, 0});
                cand.push_back({3, 4, 0});
                cand.push_back({5, 5, 0});
                break;
            case 1: // full intersection (A == B)
                cand.push_back({1, 1, 1});
                cand.push_back({2, 2, 2});
                cand.push_back({3, 3, 3});
                cand.push_back({4, 4, 4});
                break;
            case 2: // A subset of B
                cand.push_back({1, 2, 1});
                cand.push_back({2, 3, 2});
                cand.push_back({2, 4, 2});
                cand.push_back({3, 5, 3});
                break;
            case 3: // B subset of A
                cand.push_back({2, 1, 1});
                cand.push_back({3, 2, 2});
                cand.push_back({4, 2, 2});
                cand.push_back({5, 3, 3});
                break;
            case 4: // partial intersection (neither empty nor full)
                cand.push_back({3, 4, 1});
                cand.push_back({4, 4, 2});
                cand.push_back({5, 5, 3});
                cand.push_back({3, 5, 2});
                break;
            case 5: // N = 0, M > 0
                cand.push_back({0, 1, 0});
                cand.push_back({0, 3, 0});
                cand.push_back({0, 5, 0});
                break;
            case 6: // N > 0, M = 0
                cand.push_back({1, 0, 0});
                cand.push_back({3, 0, 0});
                cand.push_back({5, 0, 0});
                break;
        }

        // Filter candidates by remaining budget
        vector<int> goodIdx;
        for (int i = 0; i < (int)cand.size(); ++i) {
            int N = cand[i].N;
            int M = cand[i].M;
            if (N == 0 && M == 0) continue; // avoid non-sentinel 0 0
            if (N + M <= remaining) goodIdx.push_back(i);
        }

        if (goodIdx.empty()) continue; // can't fit this mode, skip

        int chosenIndex = rnd.any(goodIdx);
        NMConfig cfg = cand[chosenIndex];

        int N = cfg.N;
        int M = cfg.M;
        int C = cfg.C;

        int U = N + M - C; // size of union

        vector<int> all(U);

        // Choose style of values (small, medium, or near 1e9)
        int valueStyle = rnd.next(0, 2);
        long long base;
        if (valueStyle == 0) {
            base = rnd.next(1, 30);
        } else if (valueStyle == 1) {
            base = rnd.next(50, 500);
        } else {
            base = rnd.next((int)1e9 - 300, (int)1e9 - 200);
        }

        all[0] = (int)base;
        for (int i = 1; i < U; ++i) {
            all[i] = all[i - 1] + rnd.next(1, 10);
        }

        // Randomly assign each value to common / A-only / B-only
        vector<int> idxs(U);
        for (int i = 0; i < U; ++i) idxs[i] = i;
        shuffle(idxs.begin(), idxs.end());

        vector<int> commonIdx, onlyAIdx, onlyBIdx;
        int ptr = 0;

        for (int i = 0; i < C; ++i) commonIdx.push_back(idxs[ptr++]);
        for (int i = 0; i < N - C; ++i) onlyAIdx.push_back(idxs[ptr++]);
        for (int i = 0; i < M - C; ++i) onlyBIdx.push_back(idxs[ptr++]);

        vector<int> A, B;
        for (int id : commonIdx) {
            A.push_back(all[id]);
            B.push_back(all[id]);
        }
        for (int id : onlyAIdx) A.push_back(all[id]);
        for (int id : onlyBIdx) B.push_back(all[id]);

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        // Output this test case
        println(N, M);
        for (int x : A) println(x);
        for (int y : B) println(y);

        totalCDs += N + M;
        producedAny = true;
    }

    // Safety fallback: ensure at least one valid test case
    if (!producedAny) {
        int N = 3, M = 3, C = 2;
        int U = N + M - C; // 4

        vector<int> all(U);
        all[0] = 1;
        for (int i = 1; i < U; ++i) all[i] = all[i - 1] + 1;

        vector<int> A = {all[0], all[1], all[2]};
        vector<int> B = {all[1], all[2], all[3]};

        println(N, M);
        for (int x : A) println(x);
        for (int y : B) println(y);
    }

    // Sentinel
    println(0, 0);

    return 0;
}
