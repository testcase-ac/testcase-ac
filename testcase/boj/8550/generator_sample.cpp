#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 12 : 15);

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    vector<pair<int, int>> edges;

    if (mode == 1) {
        int len = rnd.next(2, n);
        for (int i = 0; i + 1 < len; ++i) {
            edges.push_back({order[i], order[i + 1]});
        }
    } else if (mode == 2) {
        int center = order[0];
        bool centerWins = rnd.next(0, 1);
        int leaves = rnd.next(1, n - 1);
        for (int i = 1; i <= leaves; ++i) {
            if (centerWins) {
                edges.push_back({center, order[i]});
            } else {
                edges.push_back({order[i], center});
            }
        }
    } else if (mode == 3) {
        int cut1 = rnd.next(1, n - 1);
        int cut2 = rnd.next(cut1, n - 1);
        for (int i = 0; i < cut1; ++i) {
            for (int j = cut1; j < cut2; ++j) {
                if (rnd.next(0, 2) > 0) {
                    edges.push_back({order[i], order[j]});
                }
            }
        }
        for (int i = cut1; i < cut2; ++i) {
            for (int j = cut2; j < n; ++j) {
                if (rnd.next(0, 2) > 0) {
                    edges.push_back({order[i], order[j]});
                }
            }
        }
    } else if (mode == 4) {
        int probability = rnd.next(10, 45);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(1, 100) <= probability) {
                    edges.push_back({order[i], order[j]});
                }
            }
        }
    } else if (mode == 5) {
        int probability = rnd.next(55, 90);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(1, 100) <= probability) {
                    edges.push_back({order[i], order[j]});
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
