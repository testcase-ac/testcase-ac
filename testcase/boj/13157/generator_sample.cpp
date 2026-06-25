#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Edge {
    int to;
    vector<int> forbidden;
};

static vector<int> shuffledServersExcept(int n, int excluded) {
    vector<int> values;
    for (int v = 1; v <= n; ++v) {
        if (v != excluded) {
            values.push_back(v);
        }
    }
    shuffle(values.begin(), values.end());
    return values;
}

static void addEdge(vector<vector<Edge>>& graph, int from, int to,
                    vector<int> forbidden) {
    for (const Edge& edge : graph[from]) {
        if (edge.to == to) {
            return;
        }
    }
    sort(forbidden.begin(), forbidden.end());
    forbidden.erase(unique(forbidden.begin(), forbidden.end()), forbidden.end());
    graph[from].push_back({to, forbidden});
}

static vector<int> randomForbidden(int n, int from, int maxCount) {
    vector<int> candidates = shuffledServersExcept(n, from);
    int count = rnd.next(0, min(maxCount, static_cast<int>(candidates.size())));
    candidates.resize(count);
    sort(candidates.begin(), candidates.end());
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 2 ? 12 : 9);
    vector<int> processing(n + 1);
    for (int i = 1; i <= n; ++i) {
        processing[i] = rnd.next(0, rnd.next(0, 4) == 0 ? 1000 : 40);
    }

    vector<vector<Edge>> graph(n + 1);

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(graph, i, i + 1, randomForbidden(n, i, 1));
        }
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 1) == 1) {
                int to = rnd.next(1, n);
                if (to != i) {
                    addEdge(graph, i, to, randomForbidden(n, i, 2));
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            vector<int> forbidden;
            if (i > 1 && rnd.next(0, 1) == 1) {
                forbidden.push_back(i - 1);
            }
            addEdge(graph, i, i + 1, forbidden);
        }
        if (n >= 4) {
            addEdge(graph, 1, n, {});
            addEdge(graph, 2, n, {1});
        }
        int extra = rnd.next(0, n);
        for (int k = 0; k < extra; ++k) {
            int from = rnd.next(1, n);
            int to = rnd.next(1, n);
            if (from != to) {
                addEdge(graph, from, to, randomForbidden(n, from, 3));
            }
        }
    } else if (mode == 2) {
        for (int from = 1; from <= n; ++from) {
            double density = rnd.next(0.15, 0.55);
            for (int to = 1; to <= n; ++to) {
                if (from != to && rnd.next() < density) {
                    addEdge(graph, from, to, randomForbidden(n, from, 3));
                }
            }
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            int to = i == n ? 1 : i + 1;
            addEdge(graph, i, to, randomForbidden(n, i, 2));
        }
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 2) > 0) {
                int to = rnd.next(1, n);
                if (to != i) {
                    addEdge(graph, i, to, randomForbidden(n, i, 2));
                }
            }
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(static_cast<int>(graph[i].size()), processing[i]);
        for (const Edge& edge : graph[i]) {
            printf("%d %d", static_cast<int>(edge.forbidden.size()), edge.to);
            for (int predecessor : edge.forbidden) {
                printf(" %d", predecessor);
            }
            printf("\n");
        }
    }

    return 0;
}
