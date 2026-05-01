#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXM = 40;

    int scenario = rnd.next(0, 7);
    int N = 0;
    vector<pair<int,int>> edges;

    switch (scenario) {
        case 0: {
            // Single course, no prerequisites
            N = 1;
            break;
        }
        case 1: {
            // Random number of courses, no prerequisites
            N = rnd.next(1, 10);
            break;
        }
        case 2: {
            // Pure chain: 1->2->3->...->N
            N = rnd.next(2, 12);
            for (int i = 1; i < N; ++i)
                edges.emplace_back(i, i + 1);
            break;
        }
        case 3: {
            // Moderately dense DAG with A < B
            N = rnd.next(5, 15);
            int prob = rnd.next(40, 80); // percentage, 40%~80%
            for (int i = 1; i <= N; ++i) {
                for (int j = i + 1; j <= N; ++j) {
                    if (rnd.next(0, 99) < prob)
                        edges.emplace_back(i, j);
                }
            }
            if (edges.empty())
                edges.emplace_back(1, 2);
            break;
        }
        case 4: {
            // Layered DAG: levels of courses
            int minN = 4, maxN = 15;
            N = rnd.next(minN, maxN);
            int L = rnd.next(2, 4);
            if (L > N) L = N;

            vector<int> levelCnt(L, 1); // ensure at least one node per level
            int remaining = N - L;
            for (int i = 0; i < remaining; ++i)
                ++levelCnt[rnd.next(0, L - 1)];

            vector<vector<int>> nodes(L);
            int cur = 1;
            for (int lv = 0; lv < L; ++lv) {
                for (int k = 0; k < levelCnt[lv]; ++k)
                    nodes[lv].push_back(cur++);
            }

            for (int i = 0; i < L; ++i) {
                for (int j = i + 1; j < L; ++j) {
                    int prob = (j == i + 1 ? 70 : 40); // denser between adjacent levels
                    for (int a : nodes[i]) {
                        for (int b : nodes[j]) {
                            if (rnd.next(0, 99) < prob)
                                edges.emplace_back(a, b);
                        }
                    }
                }
            }

            // Optionally ensure each non-first-level node has at least one prerequisite
            for (int lv = 1; lv < L; ++lv) {
                for (int v : nodes[lv]) {
                    bool hasPrereq = false;
                    for (auto &e : edges) {
                        if (e.second == v) {
                            hasPrereq = true;
                            break;
                        }
                    }
                    if (!hasPrereq) {
                        int earlierLv = rnd.next(0, lv - 1);
                        int u = rnd.any(nodes[earlierLv]);
                        edges.emplace_back(u, v);
                    }
                }
            }
            break;
        }
        case 5: {
            // Hand-crafted tricky patterns
            int type = rnd.next(0, 1);
            if (type == 0) {
                // Sample from statement
                N = 3;
                edges.emplace_back(2, 3);
                edges.emplace_back(1, 2);
            } else {
                // Multiple prerequisites converging to one course
                N = 6;
                edges.emplace_back(1, 3);
                edges.emplace_back(1, 4);
                edges.emplace_back(2, 4);
                edges.emplace_back(2, 5);
                edges.emplace_back(3, 6);
                edges.emplace_back(4, 6);
                edges.emplace_back(5, 6);
            }
            break;
        }
        case 6: {
            // Star from course 1, plus some extra dependencies
            N = rnd.next(3, 12);
            for (int i = 2; i <= N; ++i)
                edges.emplace_back(1, i);
            for (int i = 3; i <= N; ++i) {
                if (rnd.next(0, 1) == 1) {
                    int u = rnd.next(2, i - 1);
                    edges.emplace_back(u, i);
                }
            }
            break;
        }
        case 7: {
            // Bounded number of prerequisites per course
            N = rnd.next(5, 15);
            for (int b = 2; b <= N; ++b) {
                int upper = min(b - 1, 3);
                int k = rnd.next(0, upper);
                if (k == 0) continue;
                vector<int> cand;
                for (int i = 1; i < b; ++i)
                    cand.push_back(i);
                shuffle(cand.begin(), cand.end());
                for (int t = 0; t < k; ++t)
                    edges.emplace_back(cand[t], b);
            }
            break;
        }
    }

    // Limit the total number of edges and shuffle them
    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > MAXM)
        edges.resize(MAXM);

    println(N, (int)edges.size());
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
