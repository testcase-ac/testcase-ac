#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(5);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.push_back({center, v});
            }
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v / 2, v});
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({rnd.next(1, v - 1), v});
        }
    } else {
        int firstHub = rnd.next(1, n);
        int secondHub = rnd.next(1, n - 1);
        if (secondHub >= firstHub) {
            ++secondHub;
        }

        edges.push_back({firstHub, secondHub});
        for (int v = 1; v <= n; ++v) {
            if (v == firstHub || v == secondHub) {
                continue;
            }
            edges.push_back({rnd.next(2) == 0 ? firstHub : secondHub, v});
        }
    }

    shuffle(edges.begin(), edges.end());

    double forwardBias = rnd.next();
    for (auto& edge : edges) {
        if (rnd.next() > forwardBias) {
            swap(edge.first, edge.second);
        }
    }

    println(n);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
