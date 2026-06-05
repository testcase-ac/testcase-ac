#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(3, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i - 1, i);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.emplace_back(center, i);
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n - 1);
        for (int i = 2; i <= spine; ++i) {
            edges.emplace_back(i - 1, i);
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, spine), i);
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i / 2, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, i - 1), i);
        }
    }

    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end());

    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(2)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    println(vertices[0], vertices[1], vertices[2]);

    return 0;
}
