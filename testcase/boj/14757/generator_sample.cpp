#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> makeChain(int n, const vector<int>& order) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({order[i - 1], order[i]});
    }
    return edges;
}

static vector<pair<int, int>> makeRandomDag(int n, const vector<int>& order, double edgeProb) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (rnd.next() < edgeProb) {
                edges.push_back({order[i], order[j]});
            }
        }
    }
    if (edges.empty()) {
        edges.push_back({order[0], order[1]});
    }
    return edges;
}

static vector<pair<int, int>> makeCycleCase(int n, const vector<int>& labels) {
    vector<pair<int, int>> edges;
    int cycleSize = rnd.next(2, min(n, 5));
    for (int i = 0; i < cycleSize; ++i) {
        edges.push_back({labels[i], labels[(i + 1) % cycleSize]});
    }
    for (int i = cycleSize; i < n; ++i) {
        int from = labels[rnd.next(0, i - 1)];
        edges.push_back({from, labels[i]});
    }
    return edges;
}

static void addExtraEdges(vector<pair<int, int>>& edges, int n, int target) {
    set<pair<int, int>> seen(edges.begin(), edges.end());
    int attempts = 0;
    while ((int)edges.size() < target && attempts < 2000) {
        ++attempts;
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (a == b || seen.count({a, b})) {
            continue;
        }
        seen.insert({a, b});
        edges.push_back({a, b});
    }
}

static void printCase(int n, vector<pair<int, int>> edges) {
    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(5, 8);
    for (int tc = 0; tc < caseCount; ++tc) {
        int n = rnd.next(2, 12);
        vector<int> labels(n);
        for (int i = 0; i < n; ++i) {
            labels[i] = i + 1;
        }
        shuffle(labels.begin(), labels.end());

        int mode = rnd.next(0, 5);
        vector<pair<int, int>> edges;
        if (mode == 0) {
            edges = makeChain(n, labels);
        } else if (mode == 1) {
            edges = makeRandomDag(n, labels, rnd.next(0.15, 0.45));
        } else if (mode == 2) {
            edges = makeCycleCase(n, labels);
        } else if (mode == 3) {
            int split = rnd.next(1, n - 1);
            vector<int> first(labels.begin(), labels.begin() + split);
            vector<int> second(labels.begin() + split, labels.end());
            edges = makeChain((int)first.size(), first);
            vector<pair<int, int>> secondEdges = makeChain((int)second.size(), second);
            edges.insert(edges.end(), secondEdges.begin(), secondEdges.end());
            if (edges.empty()) {
                edges.push_back({labels[0], labels[1]});
            }
        } else if (mode == 4) {
            edges = makeRandomDag(n, labels, rnd.next(0.55, 0.9));
        } else {
            edges = makeCycleCase(n, labels);
            addExtraEdges(edges, n, rnd.next((int)edges.size(), min(n * (n - 1), (int)edges.size() + 8)));
        }

        printCase(n, edges);
    }

    println(0, 0);
    return 0;
}
