#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0;
    int X = 1;
    vector<pair<int,int>> edges;

    int type = rnd.next(0, 6); // choose scenario

    switch (type) {
        // Type 0: very small, possibly no edges
        case 0: {
            N = rnd.next(1, 5);
            X = rnd.next(1, N);
            // edges stays empty
            break;
        }

        // Type 1: simple chain
        case 1: {
            N = rnd.next(2, 10);
            edges.clear();
            for (int i = 1; i < N; ++i) {
                edges.emplace_back(i, i + 1);
            }
            X = rnd.next(1, N);
            break;
        }

        // Type 2: diamond + optional tail (tests double-counting of ancestors)
        case 2: {
            N = rnd.next(4, 7);
            edges.clear();
            // base diamond: 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4
            edges.emplace_back(1, 2);
            edges.emplace_back(1, 3);
            edges.emplace_back(2, 4);
            edges.emplace_back(3, 4);
            // extend tail from 4 to N
            for (int v = 4; v < N; ++v) {
                edges.emplace_back(v, v + 1);
            }
            X = N; // last node
            break;
        }

        // Type 3: multiple components, X has outgoing edges but no incoming (answer 0)
        case 3: {
            N = rnd.next(4, 8);
            edges.clear();
            // Component 1: small chain
            if (N >= 3) {
                edges.emplace_back(1, 2);
                edges.emplace_back(2, 3);
            }
            // Choose X = 4; ensure it has no incoming edges
            X = 4;
            if (N >= 5) {
                edges.emplace_back(4, 5);
            }
            if (N >= 6) {
                edges.emplace_back(4, 6);
            }
            if (N >= 7) {
                edges.emplace_back(5, 7);
            }
            if (N >= 8) {
                edges.emplace_back(6, 8);
            }
            break;
        }

        // Type 4: medium-dense random DAG, X is last in topological order
        case 4: {
            N = rnd.next(5, 12);
            edges.clear();

            vector<int> ord(N);
            for (int i = 0; i < N; ++i) ord[i] = i + 1;
            shuffle(ord.begin(), ord.end());

            X = ord.back();

            vector<pair<int,int>> cand;
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    cand.emplace_back(ord[i], ord[j]);
                }
            }
            shuffle(cand.begin(), cand.end());

            int candSize = (int)cand.size();
            int Mtarget = rnd.wnext(candSize, 2) + 1; // bias towards larger
            if (Mtarget > candSize) Mtarget = candSize;
            if (Mtarget > 40) Mtarget = 40;

            edges.assign(cand.begin(), cand.begin() + Mtarget);

            bool hasIncomingX = false;
            for (auto &e : edges) {
                if (e.second == X) {
                    hasIncomingX = true;
                    break;
                }
            }
            // Ensure at least one prerequisite for X
            if (!hasIncomingX) {
                int idx = rnd.next(0, N - 2);
                int u = ord[idx];
                edges.emplace_back(u, X);
            }
            break;
        }

        // Type 5: sparse random DAG, X arbitrary
        case 5: {
            N = rnd.next(8, 15);
            edges.clear();

            vector<int> ord(N);
            for (int i = 0; i < N; ++i) ord[i] = i + 1;
            shuffle(ord.begin(), ord.end());

            vector<pair<int,int>> cand;
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    cand.emplace_back(ord[i], ord[j]);
                }
            }
            shuffle(cand.begin(), cand.end());

            int candSize = (int)cand.size();
            int maxEdges = min(candSize, N + 5); // keep it sparse
            int Mtarget = 0;
            if (maxEdges > 0) {
                Mtarget = rnd.wnext(maxEdges + 1, -2); // bias towards smaller
                if (Mtarget > maxEdges) Mtarget = maxEdges;
            }
            edges.assign(cand.begin(), cand.begin() + Mtarget);

            X = rnd.next(1, N);
            break;
        }

        // Type 6: layered DAG (3 layers), many indirect ancestors
        case 6: {
            N = rnd.next(6, 12);
            edges.clear();

            int s1 = rnd.next(1, N - 2);
            int s2 = rnd.next(1, N - s1 - 1);
            int s3 = N - s1 - s2;

            vector<int> layer1, layer2, layer3;
            int cur = 1;
            for (int i = 0; i < s1; ++i) layer1.push_back(cur++);
            for (int i = 0; i < s2; ++i) layer2.push_back(cur++);
            for (int i = 0; i < s3; ++i) layer3.push_back(cur++);

            vector<vector<char>> used(N + 1, vector<char>(N + 1, 0));
            auto addEdgeLocal = [&](int a, int b) {
                if (a == b) return;
                if (!used[a][b]) {
                    used[a][b] = 1;
                    edges.emplace_back(a, b);
                }
            };

            // Ensure each layer2 node has at least one parent in layer1
            for (int v : layer2) {
                int u = rnd.any(layer1);
                addEdgeLocal(u, v);
            }
            // Ensure each layer3 node has at least one parent in layer2 or layer1
            for (int w : layer3) {
                int parent;
                if (!layer2.empty() && rnd.next(0, 1) == 0) parent = rnd.any(layer2);
                else parent = rnd.any(layer1);
                addEdgeLocal(parent, w);
            }
            // Extra edges between layers for complexity
            for (int u : layer1) {
                for (int v : layer2) {
                    if (rnd.next(0, 2) == 0) addEdgeLocal(u, v);
                }
            }
            for (int v : layer2) {
                for (int w : layer3) {
                    if (rnd.next(0, 1) == 0) addEdgeLocal(v, w);
                }
            }
            for (int u : layer1) {
                for (int w : layer3) {
                    if (rnd.next(0, 3) == 0) addEdgeLocal(u, w);
                }
            }

            X = rnd.any(layer3); // last layer
            break;
        }
    }

    int M = (int)edges.size();
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    println(X);

    return 0;
}
