#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(6, 14);
    }

    vector<long long> x(n + 1), y(n + 1);
    set<pair<long long, long long>> usedPoints;
    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            x[i] = rnd.next(-5, 5);
            y[i] = 0;
        } else if (mode == 2 && i % 5 == 0) {
            x[i] = rnd.next(-30, 30);
            y[i] = 0;
        } else {
            x[i] = rnd.next(-30, 30);
            y[i] = rnd.next(1, 12);
        }

        while (!usedPoints.insert({x[i], y[i]}).second) {
            x[i] = rnd.next(-30, 30);
            if (i == 1 || (mode == 2 && i % 5 == 0)) {
                y[i] = 0;
            } else {
                y[i] = rnd.next(1, 12);
            }
        }
    }

    vector<pair<int, int>> edges;
    set<pair<int, int>> usedEdges;
    auto addEdge = [&](int a, int b) {
        if (a == b || y[a] == y[b]) {
            return false;
        }
        auto e = minmax(a, b);
        if (!usedEdges.insert(e).second) {
            return false;
        }
        edges.push_back(e);
        return true;
    };

    for (int i = 2; i <= n; ++i) {
        vector<int> candidates;
        for (int j = 1; j < i; ++j) {
            if (y[j] != y[i]) {
                candidates.push_back(j);
            }
        }
        addEdge(i, rnd.any(candidates));
    }

    vector<pair<int, int>> extraCandidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (y[i] != y[j] && !usedEdges.count({i, j})) {
                extraCandidates.push_back({i, j});
            }
        }
    }
    shuffle(extraCandidates.begin(), extraCandidates.end());

    int extraLimit = mode == 3 ? (int)extraCandidates.size() : min((int)extraCandidates.size(), n);
    int extraCount = extraLimit == 0 ? 0 : rnd.next(0, extraLimit);
    for (int i = 0; i < extraCount; ++i) {
        addEdge(extraCandidates[i].first, extraCandidates[i].second);
    }

    vector<char> colors = {'R', 'G', 'B'};
    vector<char> edgeColors;
    for (int i = 0; i < (int)edges.size(); ++i) {
        if (mode == 4) {
            edgeColors.push_back(i % 2 == 0 ? 'G' : rnd.any(colors));
        } else if (mode == 5) {
            edgeColors.push_back(i % 3 == 0 ? 'B' : 'R');
        } else {
            edgeColors.push_back(rnd.any(colors));
        }
    }

    vector<int> order(edges.size());
    for (int i = 0; i < (int)order.size(); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    println(n, (int)edges.size());
    for (int i = 1; i <= n; ++i) {
        println(x[i], y[i]);
    }
    for (int id : order) {
        println(edges[id].first, edges[id].second, edgeColors[id]);
    }

    return 0;
}
