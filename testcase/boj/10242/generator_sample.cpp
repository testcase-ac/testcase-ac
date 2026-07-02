#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

static vector<int> makeParties(int n, int mode) {
    vector<int> party(n);
    if (mode == 0) {
        int value = rnd.next(0, 1);
        fill(party.begin(), party.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) party[i] = i % 2;
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) party[i] = i < split ? first : 1 - first;
    } else {
        for (int i = 0; i < n; ++i) party[i] = rnd.next(0, 1);
        party[rnd.next(0, n - 1)] = 0;
        party[rnd.next(0, n - 1)] = 1;
    }
    return party;
}

static set<pair<int, int>> makeGraph(int n, int mode) {
    set<pair<int, int>> edges;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) addEdge(edges, rnd.next(1, v - 1), v);
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) addEdge(edges, 1, v);
    } else if (mode == 2) {
        for (int v = 1; v < n; ++v) addEdge(edges, v, v + 1);
    } else {
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) addEdge(edges, a, b);
        }
    }

    double extraProb = rnd.next(0.0, 0.45);
    if (mode != 3) {
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (!edges.count({a, b}) && rnd.next() < extraProb) {
                    addEdge(edges, a, b);
                }
            }
        }
    }

    return edges;
}

static void printCase(int n, int graphMode, int partyMode) {
    vector<int> party = makeParties(n, partyMode);
    set<pair<int, int>> edgeSet = makeGraph(n, graphMode);
    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());

    println(n, static_cast<int>(edges.size()));
    println(party);
    for (const auto& edge : edges) println(edge.first, edge.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 6);
    for (int tc = 0; tc < t; ++tc) {
        int graphMode = tc % 4;
        int partyMode = rnd.next(0, 3);
        int n;
        if (graphMode == 3) {
            n = rnd.next(2, 7);
        } else {
            n = rnd.next(2, 12);
        }
        printCase(n, graphMode, partyMode);
    }

    println(0, 0);
    return 0;
}
