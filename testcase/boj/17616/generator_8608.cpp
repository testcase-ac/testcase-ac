#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 6);

    int N = 0;
    int X = 1;
    vector<int> perm;
    vector<pair<int,int>> edges;

    if (scenario == 1) {
        // Scenario 1: Simple chain
        N = rnd.next(2, 12);
        perm.resize(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        X = rnd.next(1, N);

        for (int i = 0; i < N - 1; i++) {
            edges.emplace_back(perm[i], perm[i + 1]);
        }
    } else if (scenario == 2) {
        // Scenario 2: Complete comparison
        N = rnd.next(2, 10);
        perm.resize(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        X = rnd.next(1, N);

        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                edges.emplace_back(perm[i], perm[j]);
            }
        }
    } else if (scenario == 3) {
        // Scenario 3: Random sparse/dense, sometimes X isolated
        N = rnd.next(4, 12);
        perm.resize(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());

        double probs[3] = {0.15, 0.3, 0.6};
        double p = probs[rnd.next(0, 2)];

        bool makeIsolatedX = (rnd.next(0, 1) == 1);
        int posX = rnd.next(0, N - 1);
        X = perm[posX];

        if (makeIsolatedX) {
            for (int i = 0; i < N; i++) {
                if (i == posX) continue;
                for (int j = i + 1; j < N; j++) {
                    if (j == posX) continue;
                    if (rnd.next() < p) {
                        edges.emplace_back(perm[i], perm[j]);
                    }
                }
            }
            if (edges.empty()) {
                // ensure at least one edge among others
                int a = 0;
                if (a == posX) a++;
                int b = a + 1;
                if (b == posX) b++;
                if (b >= N) b = 0; // just in case, though N>=4
                if (a != b) {
                    int i = min(a, b), j = max(a, b);
                    edges.emplace_back(perm[i], perm[j]);
                }
            }
        } else {
            X = rnd.next(1, N);
            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    if (rnd.next() < p) {
                        edges.emplace_back(perm[i], perm[j]);
                    }
                }
            }
            if (edges.empty()) {
                edges.emplace_back(perm[0], perm[1]);
            }
        }
    } else if (scenario == 4) {
        // Scenario 4: X is best or worst with few comparisons
        N = rnd.next(3, 12);
        perm.resize(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());

        bool best = (rnd.next(0, 1) == 1);
        int posX = best ? 0 : (N - 1);
        X = perm[posX];

        double pToOthers = 0.5;
        double pAmongOthers = 0.3;

        if (best) {
            for (int j = 1; j < N; j++) {
                if (rnd.next() < pToOthers) {
                    edges.emplace_back(perm[0], perm[j]);
                }
            }
        } else {
            for (int i = 0; i < N - 1; i++) {
                if (rnd.next() < pToOthers) {
                    edges.emplace_back(perm[i], perm[N - 1]);
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (i == posX) continue;
            for (int j = i + 1; j < N; j++) {
                if (j == posX) continue;
                if (rnd.next() < pAmongOthers) {
                    edges.emplace_back(perm[i], perm[j]);
                }
            }
        }

        if (edges.empty()) {
            if (best) {
                edges.emplace_back(perm[0], perm[1]);
            } else {
                edges.emplace_back(perm[N - 2], perm[N - 1]);
            }
        }
    } else if (scenario == 5) {
        // Scenario 5: Two blocks with many cross comparisons
        N = rnd.next(4, 12);
        perm.resize(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());

        int split = rnd.next(1, N - 1); // [1, N-1]
        int posX;
        if (rnd.next(0, 1) == 0) {
            posX = rnd.next(0, split - 1);       // from better block
        } else {
            posX = rnd.next(split, N - 1);       // from worse block
        }
        X = perm[posX];

        double crossP = 0.6;
        // Cross edges from block 1 to block 2
        int crossCnt = 0;
        for (int i = 0; i < split; i++) {
            for (int j = split; j < N; j++) {
                if (rnd.next() < crossP) {
                    edges.emplace_back(perm[i], perm[j]);
                    crossCnt++;
                }
            }
        }
        if (crossCnt == 0) {
            edges.emplace_back(perm[0], perm[split]);
        }

        // Internal better block edges
        if (split >= 2) {
            for (int i = 0; i < split - 1; i++) {
                if (rnd.next() < 0.7) {
                    edges.emplace_back(perm[i], perm[i + 1]);
                }
            }
            for (int i = 0; i < split; i++) {
                for (int j = i + 2; j < split; j++) {
                    if (rnd.next() < 0.2) {
                        edges.emplace_back(perm[i], perm[j]);
                    }
                }
            }
        }

        // Internal worse block edges
        if (N - split >= 2) {
            for (int i = split; i < N - 1; i++) {
                if (rnd.next() < 0.7) {
                    edges.emplace_back(perm[i], perm[i + 1]);
                }
            }
            for (int i = split; i < N; i++) {
                for (int j = i + 2; j < N; j++) {
                    if (rnd.next() < 0.2) {
                        edges.emplace_back(perm[i], perm[j]);
                    }
                }
            }
        }
    } else if (scenario == 6) {
        // Scenario 6: Middle hub strongly connected
        N = rnd.next(5, 12);
        perm.resize(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());

        int posHub = rnd.next(1, N - 2); // not at extremes
        int hub = perm[posHub];

        bool setXasHub = (rnd.next(0, 1) == 1);
        if (setXasHub) {
            X = hub;
        } else {
            X = rnd.next(1, N);
        }

        double pLeft = 0.8;
        double pRight = 0.8;
        double pOthers = 0.2;

        // Left side (better than hub)
        for (int i = 0; i < posHub; i++) {
            if (rnd.next() < pLeft) {
                edges.emplace_back(perm[i], hub); // better -> hub
            }
        }
        // Right side (worse than hub)
        for (int j = posHub + 1; j < N; j++) {
            if (rnd.next() < pRight) {
                edges.emplace_back(hub, perm[j]); // hub -> worse
            }
        }

        // Among others, sparse edges
        for (int i = 0; i < N; i++) {
            if (i == posHub) continue;
            for (int j = i + 1; j < N; j++) {
                if (j == posHub) continue;
                if (rnd.next() < pOthers) {
                    edges.emplace_back(perm[i], perm[j]);
                }
            }
        }

        if (edges.empty()) {
            edges.emplace_back(perm[posHub - 1], hub);
        }
    }

    shuffle(edges.begin(), edges.end());
    int M = (int)edges.size();
    if (M == 0) {
        // Fallback safety: should not happen, but just in case.
        if (N < 2) {
            N = 2;
            edges.clear();
            edges.emplace_back(1, 2);
            M = 1;
            X = 1;
        } else {
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            edges.emplace_back(perm[0], perm[1]);
            M = 1;
        }
    }

    println(N, M, X);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
