#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<int> componentOf(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);
    for (auto [parent, child] : edges) {
        graph[parent].push_back(child);
        graph[child].push_back(parent);
    }

    vector<int> component(n + 1, 0);
    int componentId = 0;
    for (int start = 1; start <= n; ++start) {
        if (component[start] != 0) {
            continue;
        }
        ++componentId;
        vector<int> stack = {start};
        component[start] = componentId;
        while (!stack.empty()) {
            int current = stack.back();
            stack.pop_back();
            for (int next : graph[current]) {
                if (component[next] == 0) {
                    component[next] = componentId;
                    stack.push_back(next);
                }
            }
        }
    }
    return component;
}

pair<int, int> pickQuery(int n, const vector<pair<int, int>>& edges, bool preferConnected) {
    vector<int> component = componentOf(n, edges);
    vector<pair<int, int>> candidates;

    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            bool connected = component[a] == component[b];
            if (connected == preferConnected) {
                candidates.push_back({a, b});
            }
        }
    }

    if (candidates.empty()) {
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }
    }

    pair<int, int> result = rnd.any(candidates);
    if (rnd.next(0, 1)) {
        swap(result.first, result.second);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 15);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 12);
        for (int child = 2; child <= n; ++child) {
            edges.push_back({child - 1, child});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 15);
        int root = 1;
        for (int child = 2; child <= n; ++child) {
            edges.push_back({root, child});
        }
    } else if (mode == 2) {
        n = rnd.next(6, 15);
        int used = rnd.next(4, n);
        for (int child = 2; child <= used; ++child) {
            int parent = max(1, child / rnd.next(2, 3));
            edges.push_back({parent, child});
        }
    } else if (mode == 3) {
        n = rnd.next(2, 15);
        int m = rnd.next(0, n - 1);
        for (int child = 2; child <= n && static_cast<int>(edges.size()) < m; ++child) {
            if (rnd.next(0, 2) != 0) {
                edges.push_back({rnd.next(1, child - 1), child});
            }
        }
        while (static_cast<int>(edges.size()) < m) {
            int child = rnd.next(2, n);
            bool hasParent = false;
            for (auto [_, existingChild] : edges) {
                hasParent = hasParent || existingChild == child;
            }
            if (!hasParent) {
                edges.push_back({rnd.next(1, child - 1), child});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(4, 15);
        int split = rnd.next(2, n - 1);
        for (int child = 2; child <= split; ++child) {
            edges.push_back({rnd.next(1, child - 1), child});
        }
        for (int child = split + 2; child <= n; ++child) {
            edges.push_back({rnd.next(split + 1, child - 1), child});
        }
    } else {
        n = rnd.next(2, 15);
        if (rnd.next(0, 1)) {
            edges.push_back({1, 2});
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
    }
    shuffle(edges.begin(), edges.end());

    bool preferConnected = mode != 4 && rnd.next(0, 3) != 0;
    pair<int, int> query = pickQuery(n, edges, preferConnected);

    println(n);
    println(query.first, query.second);
    println(static_cast<int>(edges.size()));
    for (auto [parent, child] : edges) {
        println(parent, child);
    }

    return 0;
}
