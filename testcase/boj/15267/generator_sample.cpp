#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

void addPath(vector<pair<int, int>>& edges, int first, int count) {
    for (int i = 0; i + 1 < count; ++i) {
        edges.push_back({first + i, first + i + 1});
    }
}

void addStar(vector<pair<int, int>>& edges, int center, int firstLeaf, int leafCount) {
    for (int i = 0; i < leafCount; ++i) {
        edges.push_back({center, firstLeaf + i});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 40);
        addPath(edges, 1, n);
    } else if (mode == 1) {
        n = rnd.next(2, 45);
        addStar(edges, 1, 2, n - 1);
    } else if (mode == 2) {
        int handle = rnd.next(2, 20);
        int leaves = rnd.next(1, 25);
        n = handle + leaves;
        addPath(edges, 1, handle);
        addStar(edges, handle, handle + 1, leaves);
    } else if (mode == 3) {
        n = rnd.next(3, 55);
        for (int v = 2; v <= n; ++v) {
            int spread = rnd.next(0, 2);
            int parent = spread == 0 ? rnd.next(1, v - 1) : max(1, v - rnd.next(1, min(v - 1, 5)));
            edges.push_back({parent, v});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 63);
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v / 2, v});
        }
    } else {
        int blockSize = rnd.next(2, 8);
        int blocks = rnd.next(2, 8);
        n = blockSize * blocks;
        for (int block = 0; block < blocks; ++block) {
            int base = block * blockSize + 1;
            if (rnd.next(0, 1) == 0) {
                addPath(edges, base, blockSize);
            } else {
                addStar(edges, base, base + 1, blockSize - 1);
            }
        }
        for (int block = 1; block < blocks; ++block) {
            int previousRoot = (block - 1) * blockSize + 1;
            int currentRoot = block * blockSize + 1;
            edges.push_back({previousRoot, currentRoot});
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(label[u], label[v]);
    }

    return 0;
}
