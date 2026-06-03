#include "testlib.h"

#include <algorithm>
#include <array>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

char randomSchool(int mode, int index) {
    if (mode == 0) {
        return char('A' + rnd.next(5));
    }
    if (mode == 1) {
        return char('A' + (index % 5));
    }
    if (mode == 2) {
        int favored = rnd.next(5);
        return char('A' + (rnd.next(100) < 65 ? favored : rnd.next(5)));
    }
    return char('A' + rnd.wnext(5, 2));
}

void addEdge(vector<Edge>& edges, set<Edge>& used, int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    if (u != v && used.insert({u, v}).second) {
        edges.push_back({u, v});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(5, 14);
    }

    vector<Edge> edges;
    set<Edge> used;

    if (n > 1) {
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) {
            vertices[i] = i + 1;
        }
        shuffle(vertices.begin(), vertices.end());

        for (int i = 1; i < n; ++i) {
            int parent = vertices[rnd.next(i)];
            addEdge(edges, used, vertices[i], parent);
        }

        if (mode >= 2) {
            for (int i = 0; i < n; ++i) {
                addEdge(edges, used, i + 1, (i + 1) % n + 1);
            }
        }

        vector<Edge> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (!used.count({u, v})) {
                    candidates.push_back({u, v});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int extraLimit = static_cast<int>(candidates.size());
        int extra = 0;
        if (mode == 1) {
            extra = rnd.next(0, min(extraLimit, n / 2));
        } else if (mode == 2) {
            extra = rnd.next(0, min(extraLimit, n));
        } else {
            extra = rnd.next(min(extraLimit, n), extraLimit);
        }

        for (int i = 0; i < extra; ++i) {
            addEdge(edges, used, candidates[i].first, candidates[i].second);
        }

        shuffle(edges.begin(), edges.end());
    }

    int q = rnd.next(1, 12);
    println(n, static_cast<int>(edges.size()), q);

    int labelMode = rnd.next(4);
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        println(edges[i].first, edges[i].second, randomSchool(labelMode, i));
    }

    for (int qi = 0; qi < q; ++qi) {
        array<int, 5> cost{};
        int queryMode = qi % 5;
        if (queryMode == 0) {
            for (int i = 0; i < 5; ++i) {
                cost[i] = rnd.next(0, 20);
            }
        } else if (queryMode == 1) {
            int cheap = rnd.next(5);
            for (int i = 0; i < 5; ++i) {
                cost[i] = (i == cheap ? rnd.next(0, 2) : rnd.next(10, 100));
            }
        } else if (queryMode == 2) {
            int base = rnd.next(0, 10);
            for (int i = 0; i < 5; ++i) {
                cost[i] = base;
            }
        } else if (queryMode == 3) {
            for (int i = 0; i < 5; ++i) {
                cost[i] = rnd.next(0, 1) * rnd.next(0, 1000);
            }
        } else {
            for (int i = 0; i < 5; ++i) {
                cost[i] = rnd.next(0, 10000000);
            }
        }
        println(cost[0], cost[1], cost[2], cost[3], cost[4]);
    }

    return 0;
}
