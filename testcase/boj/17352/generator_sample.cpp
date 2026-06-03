#include "testlib.h"
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

static void addPath(const vector<int>& nodes, vector<pair<int, int>>& edges) {
    for (int i = 1; i < (int)nodes.size(); ++i) {
        edges.emplace_back(nodes[i - 1], nodes[i]);
    }
}

static void addStar(const vector<int>& nodes, vector<pair<int, int>>& edges) {
    if (nodes.empty()) {
        return;
    }
    int center = nodes[0];
    for (int i = 1; i < (int)nodes.size(); ++i) {
        edges.emplace_back(center, nodes[i]);
    }
}

static void addRandomTree(const vector<int>& nodes, vector<pair<int, int>>& edges) {
    for (int i = 1; i < (int)nodes.size(); ++i) {
        edges.emplace_back(nodes[i], nodes[rnd.next(i)]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(5);
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode == 1) {
        n = rnd.next(3, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 10);
    } else {
        n = rnd.next(11, 25);
    }

    int firstSize;
    int splitMode = rnd.next(4);
    if (n == 2) {
        firstSize = 1;
    } else if (splitMode == 0) {
        firstSize = 1;
    } else if (splitMode == 1) {
        firstSize = n - 1;
    } else if (splitMode == 2) {
        firstSize = n / 2;
    } else {
        firstSize = rnd.next(1, n - 1);
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());

    vector<int> left(labels.begin(), labels.begin() + firstSize);
    vector<int> right(labels.begin() + firstSize, labels.end());
    shuffle(left.begin(), left.end());
    shuffle(right.begin(), right.end());

    vector<pair<int, int>> edges;
    vector<vector<int>> components = {left, right};
    for (const auto& component : components) {
        int shape = rnd.next(3);
        if (shape == 0) {
            addPath(component, edges);
        } else if (shape == 1) {
            addStar(component, edges);
        } else {
            addRandomTree(component, edges);
        }
    }

    for (auto& edge : edges) {
        if (rnd.next(2) == 1) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
