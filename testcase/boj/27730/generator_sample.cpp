#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

int randomWeight(int mode) {
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(1, 5);
    if (mode == 2) return rnd.next(9990, 10000);
    if (mode == 3) return rnd.next(1, 10000);
    return rnd.next(1, 20) * rnd.next(1, 20);
}

void addEdge(vector<Edge>& edges, int u, int v, int weightMode) {
    edges.emplace_back(u, v, randomWeight(weightMode));
}

vector<Edge> buildTree(int n, int mode, int weightMode) {
    vector<Edge> edges;
    if (n == 1) return edges;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) addEdge(edges, v - 1, v, weightMode);
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) addEdge(edges, center, v, weightMode);
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) addEdge(edges, v / 2, v, weightMode);
    } else if (mode == 3) {
        int pathLen = rnd.next(2, n);
        for (int v = 2; v <= pathLen; ++v) addEdge(edges, v - 1, v, weightMode);
        for (int v = pathLen + 1; v <= n; ++v) addEdge(edges, rnd.next(1, pathLen), v, weightMode);
    } else {
        for (int v = 2; v <= n; ++v) addEdge(edges, rnd.next(1, v - 1), v, weightMode);
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (auto& [u, v, w] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(2)) swap(u, v);
    }
    shuffle(edges.begin(), edges.end());

    return edges;
}

int chooseSize() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 4);
    if (mode == 2) return rnd.next(5, 10);
    if (mode == 3) return rnd.next(11, 18);
    if (mode == 4) return rnd.next(19, 35);
    return rnd.next(36, 60);
}

void printTree(int n, const vector<Edge>& edges) {
    println(n);
    for (auto [u, v, w] : edges) {
        println(u, v, w);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = chooseSize();
    int m = chooseSize();

    int firstMode = n == 1 ? 0 : rnd.next(0, 4);
    int secondMode = m == 1 ? 0 : rnd.next(0, 4);
    int firstWeightMode = rnd.next(0, 4);
    int secondWeightMode = rnd.next(0, 4);

    vector<Edge> first = buildTree(n, firstMode, firstWeightMode);
    vector<Edge> second = buildTree(m, secondMode, secondWeightMode);

    printTree(n, first);
    printTree(m, second);

    return 0;
}
