#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 18);
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    vector<int> cycleSizes;
    int remaining = n;
    int mode = rnd.next(0, 4);
    if (mode == 0 || remaining < 6) {
        cycleSizes.push_back(remaining);
    } else {
        while (remaining > 0) {
            if (remaining <= 5) {
                if (cycleSizes.empty()) {
                    cycleSizes.push_back(remaining);
                } else {
                    cycleSizes.back() += remaining;
                }
                break;
            }

            int maxSize = min(remaining, 8);
            int size = rnd.next(3, maxSize);
            if (remaining - size > 0 && remaining - size < 3) {
                size = remaining - 3;
            }
            cycleSizes.push_back(size);
            remaining -= size;
        }
    }

    vector<pair<int, int>> edges;
    int offset = 0;
    for (int size : cycleSizes) {
        vector<int> cycle(vertices.begin() + offset, vertices.begin() + offset + size);
        if (rnd.next(0, 1)) {
            reverse(cycle.begin(), cycle.end());
        }
        for (int i = 0; i < size; ++i) {
            edges.emplace_back(cycle[i], cycle[(i + 1) % size]);
        }
        offset += size;
    }
    shuffle(edges.begin(), edges.end());

    vector<vector<int>> cost(n, vector<int>(n, 0));
    int costMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int value;
            if (costMode == 0) {
                value = rnd.next(0, 20);
            } else if (costMode == 1) {
                value = rnd.next(0, 1000);
            } else if (costMode == 2) {
                value = abs(i - j) * rnd.next(0, 7);
            } else if (costMode == 3) {
                value = rnd.next(0, 4) == 0 ? 0 : rnd.next(1, 60);
            } else {
                value = rnd.next(0, 1) ? rnd.next(900, 1000) : rnd.next(0, 30);
            }
            cost[i][j] = cost[j][i] = value;
        }
    }

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    for (int i = 0; i < n; ++i) {
        println(cost[i]);
    }

    return 0;
}
