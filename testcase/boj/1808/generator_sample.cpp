#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> relabelParents(const vector<int>& parent) {
    int n = (int)parent.size();
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    if (n > 2) {
        shuffle(label.begin() + 1, label.end());
    }

    vector<int> relabeled(n, -1);
    for (int v = 1; v < n; ++v) {
        relabeled[label[v]] = label[parent[v]];
    }
    return relabeled;
}

static int heightOf(const vector<int>& parent) {
    int n = (int)parent.size();
    vector<int> depth(n, 0);
    int height = 0;
    for (int v = 1; v < n; ++v) {
        depth[v] = depth[parent[v]] + 1;
        height = max(height, depth[v]);
    }
    return height;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    vector<int> parent(n, -1);

    if (mode == 0) {
        for (int v = 1; v < n; ++v) {
            parent[v] = v - 1;
        }
    } else if (mode == 1) {
        for (int v = 1; v < n; ++v) {
            parent[v] = 0;
        }
    } else if (mode == 2) {
        int stem = rnd.next(2, n);
        for (int v = 1; v < stem; ++v) {
            parent[v] = v - 1;
        }
        for (int v = stem; v < n; ++v) {
            parent[v] = rnd.next(max(0, stem - 3), stem - 1);
        }
    } else if (mode == 3) {
        for (int v = 1; v < n; ++v) {
            parent[v] = (v - 1) / rnd.next(2, 4);
        }
    } else if (mode == 4) {
        for (int v = 1; v < n; ++v) {
            parent[v] = rnd.wnext(v, -2);
        }
    } else {
        for (int v = 1; v < n; ++v) {
            parent[v] = rnd.next(0, v - 1);
        }
    }

    int height = heightOf(parent);
    vector<int> hChoices = {1, n - 1, height, max(1, height - 1)};
    hChoices.push_back(rnd.next(1, n - 1));
    int h = rnd.any(hChoices);
    h = max(1, min(n - 1, h));

    parent = relabelParents(parent);

    vector<int> vertices;
    for (int v = 1; v < n; ++v) {
        vertices.push_back(v);
    }
    shuffle(vertices.begin(), vertices.end());

    println(n);
    for (int v : vertices) {
        println(parent[v], v);
    }
    println(h);

    return 0;
}
