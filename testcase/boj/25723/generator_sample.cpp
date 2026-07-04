#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static long long edgeKey(int u, int v) {
    return (static_cast<long long>(u) << 32) | static_cast<unsigned int>(v);
}

static vector<pair<int, int>> allEdges(int n) {
    vector<pair<int, int>> edges;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            edges.push_back({u, v});
        }
    }
    return edges;
}

static pair<int, int> choosePresentEdge(const set<long long>& edges) {
    int pos = rnd.next(static_cast<int>(edges.size()));
    auto it = edges.begin();
    advance(it, pos);
    int u = static_cast<int>(*it >> 32);
    int v = static_cast<int>(*it & 0xffffffffU);
    return {u, v};
}

static pair<int, int> chooseMissingEdge(const vector<pair<int, int>>& candidates,
                                        const set<long long>& edges) {
    vector<pair<int, int>> missing;
    for (auto edge : candidates) {
        if (!edges.count(edgeKey(edge.first, edge.second))) {
            missing.push_back(edge);
        }
    }
    return rnd.any(missing);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 4);
    println(tests);

    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 5);
        int n = mode == 0 ? 1 : rnd.next(2, 12);
        vector<pair<int, int>> candidates = allEdges(n);
        shuffle(candidates.begin(), candidates.end());

        set<long long> initialEdges;
        if (n > 1) {
            if (mode == 1) {
                for (int v = 2; v <= n; ++v) {
                    int u = rnd.next(1, v - 1);
                    initialEdges.insert(edgeKey(u, v));
                }
            } else if (mode == 2) {
                int limit = rnd.next(0, min<int>(3 * n, candidates.size()));
                for (int i = 0; i < limit; ++i) {
                    initialEdges.insert(edgeKey(candidates[i].first, candidates[i].second));
                }
            } else if (mode == 3) {
                double probability = rnd.next(0.15, 0.75);
                for (auto edge : candidates) {
                    if (rnd.next() < probability) {
                        initialEdges.insert(edgeKey(edge.first, edge.second));
                    }
                }
            } else if (mode == 4) {
                for (auto edge : candidates) {
                    initialEdges.insert(edgeKey(edge.first, edge.second));
                }
                int removals = rnd.next(1, min<int>(n, candidates.size()));
                shuffle(candidates.begin(), candidates.end());
                for (int i = 0; i < removals; ++i) {
                    initialEdges.erase(edgeKey(candidates[i].first, candidates[i].second));
                }
            }
        }

        int maxK = n == 1 ? 1 : 25;
        int k = rnd.next(1, maxK);
        println(k, n, static_cast<int>(initialEdges.size()));

        vector<pair<int, int>> initialList;
        for (long long key : initialEdges) {
            int u = static_cast<int>(key >> 32);
            int v = static_cast<int>(key & 0xffffffffU);
            initialList.push_back({u, v});
        }
        shuffle(initialList.begin(), initialList.end());
        for (auto edge : initialList) {
            println(edge.first, edge.second);
        }

        vector<set<long long>> graphEdges(k + 1);
        graphEdges[1] = initialEdges;
        int totalEdges = static_cast<int>(candidates.size());

        for (int graph = 2; graph <= k; ++graph) {
            int parent;
            if (rnd.next(0, 99) < 45) {
                parent = graph - 1;
            } else {
                parent = rnd.next(1, graph - 1);
            }

            const set<long long>& parentEdges = graphEdges[parent];
            bool canAdd = static_cast<int>(parentEdges.size()) < totalEdges;
            bool canRemove = !parentEdges.empty();
            bool add = canAdd && (!canRemove || rnd.next(0, 99) < 58);

            pair<int, int> edge = add
                                      ? chooseMissingEdge(candidates, parentEdges)
                                      : choosePresentEdge(parentEdges);

            graphEdges[graph] = parentEdges;
            long long key = edgeKey(edge.first, edge.second);
            if (add) {
                graphEdges[graph].insert(key);
                println(parent, "add", edge.first, edge.second);
            } else {
                graphEdges[graph].erase(key);
                println(parent, "remove", edge.first, edge.second);
            }
        }
    }

    return 0;
}
