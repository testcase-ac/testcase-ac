#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 20);
    int mode = rnd.next(0, 4);

    vector<vector<int>> adj(n, vector<int>(n, 0));
    vector<int> component(n);
    iota(component.begin(), component.end(), 0);

    auto addEdge = [&](int a, int b) {
        if (a != b) {
            adj[a][b] = 1;
            adj[b][a] = 1;
        }
    };

    if (mode == 0) {
        // One connected component with extra random edges.
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            addEdge(order[i - 1], order[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(0, 2) == 0) addEdge(i, j);
            }
        }
        fill(component.begin(), component.end(), 0);
    } else if (mode == 1) {
        // Several internally connected components and no cross edges.
        int groups = n == 1 ? 1 : rnd.next(2, min(n, 4));
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        for (int i = 0; i < n; ++i) {
            component[order[i]] = i % groups;
        }
        for (int g = 0; g < groups; ++g) {
            vector<int> nodes;
            for (int i = 0; i < n; ++i) {
                if (component[i] == g) nodes.push_back(i);
            }
            for (int i = 1; i < (int)nodes.size(); ++i) {
                addEdge(nodes[i - 1], nodes[i]);
            }
            for (int i = 0; i < (int)nodes.size(); ++i) {
                for (int j = i + 1; j < (int)nodes.size(); ++j) {
                    if (rnd.next(0, 3) == 0) addEdge(nodes[i], nodes[j]);
                }
            }
        }
    } else if (mode == 2) {
        // Sparse arbitrary graph, then derive components for the plan.
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(0, 5) == 0) addEdge(i, j);
            }
        }
        for (int i = 0; i < n; ++i) component[i] = i;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (adj[i][j] && component[i] != component[j]) {
                        int from = component[j], to = component[i];
                        for (int k = 0; k < n; ++k) {
                            if (component[k] == from) component[k] = to;
                        }
                        changed = true;
                    }
                }
            }
        }
    } else {
        // Path-like graph to exercise transitive travel through intermediates.
        for (int i = 1; i < n; ++i) addEdge(i - 1, i);
        if (n > 2 && rnd.next(0, 1)) {
            int cut = rnd.next(1, n - 1);
            adj[cut - 1][cut] = adj[cut][cut - 1] = 0;
        }
        for (int i = 0; i < n; ++i) component[i] = i;
        int current = 0;
        component[0] = current;
        for (int i = 1; i < n; ++i) {
            if (!adj[i - 1][i]) ++current;
            component[i] = current;
        }
    }

    vector<int> plan;
    bool sameComponentPlan = rnd.next(0, 1) || n == 1;
    if (sameComponentPlan) {
        int chosen = rnd.any(component);
        vector<int> candidates;
        for (int i = 0; i < n; ++i) {
            if (component[i] == chosen) candidates.push_back(i);
        }
        for (int i = 0; i < m; ++i) plan.push_back(rnd.any(candidates) + 1);
    } else {
        for (int i = 0; i < m; ++i) plan.push_back(rnd.next(1, n));
    }

    println(n);
    println(m);
    for (int i = 0; i < n; ++i) {
        println(adj[i]);
    }
    println(plan);

    return 0;
}
