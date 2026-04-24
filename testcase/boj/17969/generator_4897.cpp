#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of leaves L between 3 and 7 -> total nodes n = 2*L - 2 (min 4, max 12)
    int L = rnd.next(3, 7);
    // Weight cap and bias for diversity
    int maxW = rnd.next(5, 50);
    int bias = rnd.next(-2, 2);

    vector<tuple<int,int,int>> edges;
    int cur = 0;
    // Start with one internal node and 3 leaves
    int root = ++cur;
    for (int i = 0; i < 3; i++) {
        int leaf = ++cur;
        int w = rnd.wnext(maxW, bias) + 1;
        edges.emplace_back(root, leaf, w);
    }
    // Add remaining leaves by subdividing a random edge
    for (int newLeaf = 4; newLeaf <= L; newLeaf++) {
        int eidx = rnd.next((int)edges.size() - 1);
        auto tup = edges[eidx];
        int u = get<0>(tup), v = get<1>(tup);
        // remove the chosen edge
        edges[eidx] = edges.back();
        edges.pop_back();
        // create a new internal node and a new leaf
        int x = ++cur;
        int leaf = ++cur;
        // two edges replacing the old one
        int w1 = rnd.wnext(maxW, bias) + 1;
        int w2 = rnd.wnext(maxW, bias) + 1;
        edges.emplace_back(u, x, w1);
        edges.emplace_back(x, v, w2);
        // edge to the new leaf
        int wL = rnd.wnext(maxW, bias) + 1;
        edges.emplace_back(x, leaf, wL);
    }
    int n = cur;
    // Shuffle edge output order for diversity
    shuffle(edges.begin(), edges.end());

    // Output
    println(n);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }
    return 0;
}
