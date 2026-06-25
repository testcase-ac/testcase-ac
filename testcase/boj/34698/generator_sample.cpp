#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> shortestDistances(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
    }

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    vector<int> queue;
    for (int s = 1; s <= n; ++s) {
        dist[s][s] = 0;
        queue.clear();
        queue.push_back(s);
        for (int head = 0; head < int(queue.size()); ++head) {
            int u = queue[head];
            for (int v : adj[u]) {
                if (dist[s][v] != -1) {
                    continue;
                }
                dist[s][v] = dist[s][u] + 1;
                queue.push_back(v);
            }
        }
    }
    return dist;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 12);
    int mode = rnd.next(4);

    vector<pair<int, int>> edges;
    set<pair<int, int>> simpleEdges;
    auto addEdge = [&](int a, int b, bool allowDuplicate = false) {
        if (a == b) {
            return;
        }
        if (allowDuplicate || simpleEdges.insert({a, b}).second) {
            edges.push_back({a, b});
        }
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 2; j <= n; ++j) {
                if (rnd.next(100) < 25) {
                    addEdge(i, j);
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            addEdge(i, i % n + 1);
        }
        for (int i = 1; i <= n; ++i) {
            int j = rnd.next(1, n);
            addEdge(i, j);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= split; ++i) {
            for (int j = split + 1; j <= n; ++j) {
                if (rnd.next(100) < 45) {
                    addEdge(i, j);
                }
            }
        }
        for (int i = 1; i < split; ++i) {
            addEdge(i, i + 1);
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && rnd.next(100) < 18) {
                    addEdge(i, j);
                }
            }
        }
        if (edges.empty()) {
            addEdge(1, 2);
        }
    }

    int duplicates = rnd.next(0, min(3, int(edges.size())));
    for (int i = 0; i < duplicates; ++i) {
        edges.push_back(rnd.any(edges));
    }
    shuffle(edges.begin(), edges.end());

    auto dist = shortestDistances(n, edges);

    int q = rnd.next(4, 14);
    vector<vector<int>> queries;
    for (int qi = 0; qi < q; ++qi) {
        int kind = rnd.next(5);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        vector<int> query = {a, b, 0};

        if (kind == 0) {
            query[1] = rnd.next(1, n);
        } else if (kind == 1) {
            query[1] = a;
        } else {
            while (b == a) {
                b = rnd.next(1, n);
            }
            query[1] = b;

            vector<int> candidates;
            for (int x = 1; x <= n; ++x) {
                if (x != a && x != b) {
                    candidates.push_back(x);
                }
            }
            shuffle(candidates.begin(), candidates.end());

            if (kind == 2 && dist[a][b] != -1) {
                vector<int> onShortest;
                for (int x : candidates) {
                    if (dist[a][x] != -1 && dist[x][b] != -1 &&
                        dist[a][x] + dist[x][b] == dist[a][b]) {
                        onShortest.push_back(x);
                    }
                }
                int k = min(int(onShortest.size()), rnd.next(1, min(3, n - 2)));
                query[2] = k;
                for (int i = 0; i < k; ++i) {
                    query.push_back(onShortest[i]);
                }
            } else {
                int k = rnd.next(1, min(3, n - 2));
                query[2] = k;
                for (int i = 0; i < k; ++i) {
                    query.push_back(candidates[i]);
                }
            }
        }

        queries.push_back(query);
    }

    println(n, int(edges.size()));
    for (auto [a, b] : edges) {
        println(a, b);
    }
    println(int(queries.size()));
    for (const auto& query : queries) {
        println(query);
    }
}
