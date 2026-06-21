#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

int randomCost(int flavor) {
    if (flavor == 0) return rnd.next(0, 5);
    if (flavor == 1) return rnd.next(0, 100);
    if (flavor == 2) return rnd.any(vector<int>{0, 1, 999, 1000, 100000});
    return rnd.next(0, 100000);
}

void addPath(vector<Edge>& edges, int n, int flavor) {
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, i + 1, randomCost(flavor));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int c = 0;
    vector<Edge> edges;

    if (mode == 0) {
        n = 1;
        c = rnd.any(vector<int>{0, 1, 2, 10, 1000});
        int m = rnd.next(1, 8);
        for (int i = 0; i < m; ++i) {
            edges.emplace_back(1, 1, randomCost(rnd.next(0, 2)));
        }
    } else {
        n = rnd.next(2, 12);
        int flavor = rnd.next(0, 3);
        c = rnd.next(0, min(1000, rnd.next(0, 2 * n + 5)));
        addPath(edges, n, flavor);

        int extra = 0;
        if (mode == 1) {
            extra = rnd.next(0, n);
        } else if (mode == 2) {
            extra = rnd.next(n, 3 * n);
        } else if (mode == 3) {
            extra = rnd.next(2 * n, 5 * n);
        } else {
            extra = rnd.next(n * n / 2, min(80, n * n));
        }

        for (int i = 0; i < extra; ++i) {
            int from = rnd.next(1, n);
            int to = rnd.next(1, n);
            if (mode == 1 && rnd.next(0, 2) == 0) {
                from = rnd.next(1, n - 1);
                to = rnd.next(from + 1, n);
            } else if (mode == 2 && rnd.next(0, 2) == 0) {
                from = rnd.next(2, n);
                to = rnd.next(1, from - 1);
            } else if (mode == 3 && rnd.next(0, 3) == 0) {
                to = from;
            }
            edges.emplace_back(from, to, randomCost(flavor));
        }

        if (mode >= 2) {
            int parallel = rnd.next(1, n);
            for (int i = 0; i < parallel; ++i) {
                int from = rnd.next(1, n);
                int to = rnd.next(1, n);
                int copies = rnd.next(2, 4);
                for (int j = 0; j < copies; ++j) {
                    edges.emplace_back(from, to, randomCost(flavor));
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), c);
    for (auto [from, to, cost] : edges) {
        println(from, to, cost);
    }

    return 0;
}
