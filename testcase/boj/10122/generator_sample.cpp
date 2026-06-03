#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    edges.push_back({a, b});
}

void printTree(int n, vector<pair<int, int>> edges) {
    shuffle(edges.begin(), edges.end());
    println(n);
    for (auto [a, b] : edges) {
        println(a, b);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<pair<int, int>> edges;
    int n = 1;

    if (mode == 0) {
        n = rnd.next(1, 30);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        int center = rnd.next(1, n);
        for (int town = 1; town <= n; ++town) {
            if (town != center) {
                addEdge(edges, center, town);
            }
        }
    } else if (mode == 2) {
        int arms = rnd.next(3, 8);
        int len = rnd.next(1, 6);
        n = 1 + arms * len;
        int next = 2;
        for (int arm = 0; arm < arms; ++arm) {
            int prev = 1;
            for (int step = 0; step < len; ++step) {
                addEdge(edges, prev, next);
                prev = next++;
            }
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, 16);
        n = spine;
        for (int i = 1; i < spine; ++i) {
            addEdge(edges, i, i + 1);
        }
        int extraLeaves = rnd.next(1, 24);
        for (int i = 0; i < extraLeaves; ++i) {
            int attach = rnd.next(1, spine);
            addEdge(edges, attach, ++n);
        }
    } else {
        n = rnd.next(2, 45);
        for (int town = 2; town <= n; ++town) {
            int bias = rnd.next(3);
            int parent;
            if (bias == 0) {
                parent = 1;
            } else if (bias == 1) {
                parent = town - 1;
            } else {
                parent = rnd.next(1, town - 1);
            }
            addEdge(edges, parent, town);
        }
    }

    printTree(n, edges);
    return 0;
}
