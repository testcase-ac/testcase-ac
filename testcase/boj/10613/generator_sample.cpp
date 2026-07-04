#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int flow;
    int super;
};

double requiredAtRoot(int n, const vector<Edge>& edges, const vector<int>& need) {
    vector<vector<Edge>> children(n + 1);
    for (const Edge& edge : edges) {
        children[edge.from].push_back(edge);
    }

    vector<double> required(n + 1, 0.0);
    for (int node = n; node >= 1; --node) {
        if (children[node].empty()) {
            required[node] = need[node];
            continue;
        }

        double nodeRequired = 0.0;
        for (const Edge& edge : children[node]) {
            double childRequired = required[edge.to];
            double ratio = edge.flow / 100.0;
            double regular = childRequired / ratio;
            double powered = edge.super == 1 ? sqrt(childRequired) / ratio : regular;
            nodeRequired = max(nodeRequired, min(regular, powered));
        }
        required[node] = nodeRequired;
    }
    return required[1];
}

vector<int> partitionFlow(int parts) {
    if (parts == 1) {
        return {100};
    }

    vector<int> cuts;
    for (int i = 0; i < parts - 1; ++i) {
        cuts.push_back(rnd.next(1, 99));
    }
    sort(cuts.begin(), cuts.end());

    vector<int> flows;
    int previous = 0;
    for (int cut : cuts) {
        flows.push_back(cut - previous);
        previous = cut;
    }
    flows.push_back(100 - previous);

    shuffle(flows.begin(), flows.end());
    return flows;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    for (int attempt = 0; attempt < 1000; ++attempt) {
        int mode = rnd.next(0, 4);
        int n = 1;
        if (mode == 0) {
            n = 1;
        } else if (mode == 1) {
            n = rnd.next(2, 7);
        } else if (mode == 2) {
            n = rnd.next(4, 12);
        } else if (mode == 3) {
            n = rnd.next(5, 14);
        } else {
            n = rnd.next(8, 18);
        }

        vector<vector<int>> children(n + 1);
        if (mode == 1) {
            for (int node = 2; node <= n; ++node) {
                children[node - 1].push_back(node);
            }
        } else if (mode == 2) {
            for (int node = 2; node <= n; ++node) {
                children[1].push_back(node);
            }
        } else {
            for (int node = 2; node <= n; ++node) {
                int parent = rnd.next(1, node - 1);
                if (mode == 3) {
                    parent = max(1, node / 2);
                }
                children[parent].push_back(node);
            }
        }

        vector<Edge> edges;
        for (int node = 1; node <= n; ++node) {
            vector<int> flows = partitionFlow(static_cast<int>(children[node].size()));
            for (int i = 0; i < static_cast<int>(children[node].size()); ++i) {
                int super = rnd.next(0, 1);
                if (mode == 1 && rnd.next(0, 3) == 0) {
                    super = 1;
                }
                edges.push_back({node, children[node][i], flows[i], super});
            }
        }

        vector<int> need(n + 1, -1);
        for (int node = 1; node <= n; ++node) {
            if (children[node].empty()) {
                need[node] = rnd.next(1, 10);
            }
        }

        if (requiredAtRoot(n, edges, need) > 2000000000.0 + 1e-7) {
            continue;
        }

        shuffle(edges.begin(), edges.end());

        println(n);
        for (const Edge& edge : edges) {
            println(edge.from, edge.to, edge.flow, edge.super);
        }
        println(vector<int>(need.begin() + 1, need.end()));
        return 0;
    }

    println(1);
    println(1);
    return 0;
}
