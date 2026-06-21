#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addRichSubtree(int v, int parent, int depth, vector<Edge>& edges, int& nextNode) {
    if (depth == 0) {
        return;
    }
    int childCount = (parent == 0 ? 3 : 2);
    for (int i = 0; i < childCount; ++i) {
        int child = nextNode++;
        edges.emplace_back(v, child);
        addRichSubtree(child, v, depth - 1, edges, nextNode);
    }
}

vector<Edge> makeRichTree(int depth) {
    vector<Edge> edges;
    int nextNode = 2;
    addRichSubtree(1, 0, depth, edges, nextNode);
    return edges;
}

vector<Edge> makePath(int n) {
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, i + 1);
    }
    return edges;
}

vector<Edge> makeStar(int n) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(1, i);
    }
    return edges;
}

vector<Edge> makeRandomTree(int n) {
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) {
        edges.emplace_back(v, rnd.next(1, v - 1));
    }
    return edges;
}

vector<Edge> makeNearRichTree() {
    vector<Edge> edges = makeRichTree(rnd.next(2, 3));
    int n = static_cast<int>(edges.size()) + 1;

    int mode = rnd.next(3);
    if (mode == 0) {
        edges.emplace_back(rnd.next(2, n), n + 1);
    } else if (mode == 1) {
        Edge cut = edges.back();
        edges.pop_back();
        int movedLeaf = cut.second;
        int newParent = rnd.next(1, n);
        while (newParent == movedLeaf || newParent == cut.first) {
            newParent = rnd.next(1, n);
        }
        edges.emplace_back(newParent, movedLeaf);
    } else {
        edges.emplace_back(rnd.next(2, n), n + 1);
        edges.emplace_back(n + 1, n + 2);
    }
    return edges;
}

void shuffleLabelsAndEdges(vector<Edge>& edges) {
    int n = static_cast<int>(edges.size()) + 1;
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& [a, b] : edges) {
        a = label[a];
        b = label[b];
        if (rnd.next(2) == 0) {
            swap(a, b);
        }
    }
    shuffle(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<Edge> edges;
    if (mode == 0) {
        edges = makeRichTree(rnd.next(1, 4));
    } else if (mode == 1) {
        edges = makePath(rnd.next(4, 18));
    } else if (mode == 2) {
        edges = makeStar(rnd.next(4, 18));
    } else if (mode == 3) {
        edges = makeRandomTree(rnd.next(4, 24));
    } else {
        edges = makeNearRichTree();
    }

    shuffleLabelsAndEdges(edges);
    println(static_cast<int>(edges.size()) + 1);
    for (const auto& [a, b] : edges) {
        println(a, b);
    }

    return 0;
}
