#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int stoneMode = rnd.next(0, 2);
    int b = stoneMode == 0 ? 0 : stoneMode == 1 ? n : rnd.next(0, n);
    println(n, b);

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i + 1;
    shuffle(vertices.begin(), vertices.end());
    vector<int> stones(vertices.begin(), vertices.begin() + b);
    println(stones);

    int treeMode = rnd.next(0, 2);
    for (int v = 1; v < n; ++v) {
        int parent = treeMode == 0 ? 0 : treeMode == 1 ? v - 1 : rnd.next(0, v - 1);
        println(vertices[parent], vertices[v]);
    }

    int q = rnd.next(1, 20);
    println(q);
    for (int k = 0; k < q; ++k) {
        int i = rnd.next(1, n);
        println(i, rnd.next(0, min(i, b)));
    }
}
