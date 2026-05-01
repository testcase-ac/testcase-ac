#include "testlib.h"
using namespace std;

struct Group {
    int a, b, c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int kind = rnd.next(0, 6);

    int N = 0;
    vector<int> P;
    vector<Group> groups;

    if (kind == 0) {
        // Tiny random
        N = rnd.next(1, 6);
        P.resize(N);
        for (int i = 0; i < N; ++i)
            P[i] = rnd.next(0, 10);

        int M = rnd.next(0, 10);
        for (int i = 0; i < M; ++i) {
            int a = rnd.next(1, N);
            int b = rnd.next(1, N);
            int c = rnd.next(0, 10);
            groups.push_back({a, b, c});
        }
    } else if (kind == 1) {
        // Star topology around node 1
        N = rnd.next(2, 10);
        P.resize(N);
        // Center more expensive, leaves cheaper
        P[0] = rnd.next(5, 15);
        for (int i = 1; i < N; ++i)
            P[i] = rnd.next(0, 5);

        int center = 1;
        for (int i = 2; i <= N; ++i) {
            int c = rnd.next(1, 15);
            groups.push_back({center, i, c});
        }
        int extra = rnd.next(0, N + 3);
        while (extra--) {
            int a, b;
            if (rnd.next(0, 1) == 0) {
                a = center;
                b = rnd.next(2, N);
            } else {
                a = rnd.next(2, N);
                b = rnd.next(2, N);
            }
            int c = rnd.next(0, 12);
            groups.push_back({a, b, c});
        }
    } else if (kind == 2) {
        // Chain with possible chords
        N = rnd.next(2, 10);
        P.resize(N);
        for (int i = 0; i < N; ++i)
            P[i] = rnd.next(0, 4) + (i + 1); // increasing-ish

        for (int i = 1; i <= N - 1; ++i) {
            int c = rnd.next(3, 12);
            groups.push_back({i, i + 1, c});
        }
        int extra = rnd.next(0, N);
        while (extra--) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u > v) swap(u, v);
            if (u == v) {
                // make it a self-loop chord sometimes
                if (rnd.next(0, 1) == 0) {
                    // keep self-loop
                } else if (u < N) {
                    v = u + 1;
                }
            }
            int c = rnd.next(0, 8);
            groups.push_back({u, v, c});
        }
    } else if (kind == 3) {
        // Self-loop heavy
        N = rnd.next(1, 8);
        P.resize(N);
        for (int i = 0; i < N; ++i)
            P[i] = rnd.next(0, 10);

        int M = rnd.next(1, 2 * N + 4);
        for (int i = 0; i < M; ++i) {
            int a, b;
            if (N == 1 || rnd.next(0, 1) == 0) {
                a = b = rnd.next(1, N);
            } else {
                a = rnd.next(1, N);
                do {
                    b = rnd.next(1, N);
                } while (b == a);
            }
            int c = rnd.next(0, 15);
            groups.push_back({a, b, c});
        }
    } else if (kind == 4) {
        // Many zeros / near-trivial
        N = rnd.next(1, 5);
        P.resize(N);

        bool allZeroCost = (rnd.next(0, 1) == 0);
        if (allZeroCost) {
            for (int i = 0; i < N; ++i)
                P[i] = 0;
        } else {
            for (int i = 0; i < N; ++i)
                P[i] = rnd.next(0, 10);
        }

        int M = rnd.next(0, 8);
        for (int i = 0; i < M; ++i) {
            int a = rnd.next(1, N);
            int b = rnd.next(1, N);
            int c;
            if (allZeroCost) {
                c = rnd.next(0, 5);
            } else {
                // many zero revenues
                if (rnd.next(0, 9) < 7)
                    c = 0;
                else
                    c = rnd.next(1, 5);
            }
            groups.push_back({a, b, c});
        }
    } else if (kind == 5) {
        // Moderately dense
        N = rnd.next(3, 8);
        P.resize(N);
        for (int i = 0; i < N; ++i)
            P[i] = rnd.next(0, 15);

        vector<pair<int,int>> cand;
        for (int i = 1; i <= N; ++i) {
            for (int j = i; j <= N; ++j) {
                cand.push_back({i, j});
            }
        }
        shuffle(cand.begin(), cand.end());

        int maxK = min(25, (int)cand.size());
        int minK = min(3, maxK);
        int K = rnd.next(minK, maxK);

        for (int i = 0; i < K; ++i) {
            int a = cand[i].first;
            int b = cand[i].second;
            int c = rnd.next(0, 20);
            groups.push_back({a, b, c});
        }
    } else if (kind == 6) {
        // Crafted tradeoff instance
        N = 4;
        P.resize(N);
        int baseCost = rnd.next(5, 8);
        P[0] = baseCost;
        P[1] = baseCost;
        P[2] = baseCost;
        P[3] = rnd.next(0, 3);

        int c12 = rnd.next(6, 9);
        int c23 = rnd.next(6, 9);
        int c13 = rnd.next(6, 9);
        int c34 = rnd.next(2, 4);

        groups.push_back({1, 2, c12});
        groups.push_back({2, 3, c23});
        groups.push_back({1, 3, c13});
        groups.push_back({3, 4, c34});

        // A few random extras
        int extra = rnd.next(0, 3);
        while (extra--) {
            int a = rnd.next(1, N);
            int b = rnd.next(1, N);
            int c = rnd.next(0, 6);
            groups.push_back({a, b, c});
        }
    }

    int M = (int)groups.size();
    println(N, M);
    println(P);
    for (const auto &g : groups) {
        println(g.a, g.b, g.c);
    }

    return 0;
}
