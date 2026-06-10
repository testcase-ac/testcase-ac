#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int pathLen = 1;
    int extra = 0;

    if (mode == 0) {
        pathLen = 1;
        extra = rnd.next(0, 4);
    } else if (mode == 1) {
        pathLen = rnd.next(2, 5);
        extra = 0;
    } else if (mode == 2) {
        pathLen = rnd.next(2, 8);
        extra = rnd.next(1, 8);
    } else if (mode == 3) {
        pathLen = rnd.next(3, 10);
        extra = rnd.next(3, 14);
    } else if (mode == 4) {
        pathLen = rnd.next(6, 18);
        extra = rnd.next(0, 10);
    } else {
        pathLen = rnd.next(2, 12);
        extra = rnd.next(10, 24);
    }

    int n = pathLen + 1 + extra;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= pathLen; ++i) {
        edges.emplace_back(i, i + 1);
    }

    int nextVertex = pathLen + 2;
    while (nextVertex <= n) {
        int attach = 1;
        int shape = rnd.next(0, 3);
        if (shape == 0) {
            attach = rnd.next(1, pathLen + 1);
        } else if (shape == 1) {
            attach = rnd.next(1, max(1, pathLen));
        } else if (shape == 2 && nextVertex > pathLen + 2) {
            attach = rnd.next(pathLen + 2, nextVertex - 1);
        } else {
            attach = rnd.next(1, pathLen + 1);
        }

        int chain = rnd.next(1, min(4, n - nextVertex + 1));
        int prev = attach;
        for (int i = 0; i < chain && nextVertex <= n; ++i) {
            edges.emplace_back(prev, nextVertex);
            prev = nextVertex;
            ++nextVertex;
        }
    }

    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end());

    int s = perm[1];
    int e = perm[pathLen + 1];

    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, s, e);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
