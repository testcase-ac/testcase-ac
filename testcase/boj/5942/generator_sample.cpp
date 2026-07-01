#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    string rate;
};

string randomRate(bool boundaryHeavy) {
    if (boundaryHeavy) {
        vector<string> rates = {
            "0.1000001", "0.11", "0.2", "0.5", "0.99",
            "1", "1.01", "2", "5", "9.999999", "10"
        };
        return rnd.any(rates);
    }

    int scale = rnd.next(0, 3);
    if (scale == 0) {
        return to_string(rnd.next(1, 10));
    }
    if (scale == 1) {
        return "0." + to_string(rnd.next(11, 99));
    }
    return to_string(rnd.next(1, 9)) + "." + to_string(rnd.next(1, 999));
}

bool hasEdge(const vector<vector<char>>& used, int from, int to) {
    return used[from][to] != 0;
}

void addEdge(vector<Edge>& edges, vector<vector<char>>& used, int from, int to, const string& rate) {
    if (from == to || hasEdge(used, from, to)) {
        return;
    }
    used[from][to] = 1;
    edges.push_back({from, to, rate});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 4 ? rnd.next(8, 14) : rnd.next(2, 9);
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) {
        ++b;
    }

    vector<int> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = i + 1;
    }
    shuffle(nodes.begin(), nodes.end());

    vector<Edge> edges;
    vector<vector<char>> used(n + 1, vector<char>(n + 1, 0));

    bool boundaryHeavy = mode == 1 || mode == 3;
    for (int i = 0; i < n; ++i) {
        int from = nodes[i];
        int to = nodes[(i + 1) % n];
        addEdge(edges, used, from, to, randomRate(boundaryHeavy));
    }

    if (mode == 2 || mode == 3) {
        int x = nodes[0];
        int y = nodes[1];
        int z = nodes.size() >= 3 ? nodes[2] : nodes[0];
        addEdge(edges, used, x, y, "0.2");
        if (n >= 3) {
            addEdge(edges, used, y, z, "0.2");
            addEdge(edges, used, z, x, "0.2");
        } else {
            addEdge(edges, used, y, x, "0.2");
        }
    }

    int maxEdges = n * (n - 1);
    int targetEdges = n;
    if (mode == 0) {
        targetEdges = rnd.next(n, min(maxEdges, n + 3));
    } else if (mode == 4) {
        targetEdges = rnd.next(n + 4, min(maxEdges, 2 * n + 8));
    } else {
        targetEdges = rnd.next(n, min(maxEdges, 3 * n));
    }

    vector<pair<int, int>> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && !hasEdge(used, i, j)) {
                candidates.push_back({i, j});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (auto [from, to] : candidates) {
        if ((int)edges.size() >= targetEdges) {
            break;
        }
        addEdge(edges, used, from, to, randomRate(boundaryHeavy));
    }

    shuffle(edges.begin(), edges.end());

    string value = rnd.any(vector<string>{"1", "1.5", "60", "999999.25", "1000000000000"});
    println(n, (int)edges.size(), value, a, b);
    for (const Edge& edge : edges) {
        println(edge.from, edge.to, edge.rate);
    }

    return 0;
}
