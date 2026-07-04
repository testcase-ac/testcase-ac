#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Operation {
    string type;
    string result;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    int mode = rnd.next(0, 5);

    vector<Operation> operations(n + 1);
    for (int i = 1; i <= n; ++i) {
        operations[i].type = rnd.next(0, 1) == 0 ? "set" : "unset";
        operations[i].result = "false";
    }

    vector<int> indices;
    for (int i = 1; i <= n; ++i) {
        indices.push_back(i);
    }
    shuffle(indices.begin(), indices.end());

    if (mode == 1) {
        operations[indices[0]] = {"set", "true"};
    } else if (mode == 2) {
        operations[indices[0]] = {"unset", "true"};
    } else if (mode == 3 && n >= 2) {
        operations[indices[0]] = {"set", "true"};
        operations[indices[1]] = {"unset", "true"};
    } else if (mode == 4 && n >= 2) {
        operations[indices[0]] = {"unset", "true"};
        operations[indices[1]] = {"set", "true"};
    } else if (mode == 5 && n >= 2) {
        operations[indices[0]] = {rnd.next(0, 1) == 0 ? "set" : "unset", "true"};
        operations[indices[1]] = {rnd.next(0, 1) == 0 ? "set" : "unset", "true"};
    }

    vector<int> order = indices;
    shuffle(order.begin(), order.end());

    vector<pair<int, int>> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            candidates.push_back({order[i], order[j]});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    double density;
    int densityMode = rnd.next(0, 3);
    if (densityMode == 0) {
        density = rnd.next(0.0, 0.15);
    } else if (densityMode == 1) {
        density = rnd.next(0.15, 0.40);
    } else if (densityMode == 2) {
        density = rnd.next(0.40, 0.75);
    } else {
        density = rnd.next(0.75, 1.0);
    }

    vector<pair<int, int>> edges;
    for (auto edge : candidates) {
        if (rnd.next() < density) {
            edges.push_back(edge);
        }
    }

    int cap = min<int>(100, candidates.size());
    if ((int)edges.size() > cap) {
        shuffle(edges.begin(), edges.end());
        edges.resize(cap);
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(operations[i].type, operations[i].result);
    }
    println((int)edges.size());
    for (auto [from, to] : edges) {
        println(from, to);
    }

    return 0;
}
