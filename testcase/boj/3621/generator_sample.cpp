#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int d;
    int mode = rnd.next(6);

    if (mode == 0) {
        n = rnd.next(2, 8);
        d = rnd.next(2, n);
    } else if (mode == 1) {
        n = rnd.next(6, 14);
        d = 2;
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        d = rnd.next(2, min(n, 4));
    } else if (mode == 3) {
        n = rnd.next(10, 25);
        d = rnd.next(max(2, n / 2), n);
    } else if (mode == 4) {
        n = rnd.next(20, 60);
        d = rnd.next(2, min(n, 6));
    } else {
        n = rnd.next(40, 120);
        d = rnd.next(2, n);
    }

    vector<int> child(n + 1, 0);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            child[i] = rnd.next(0, i - 1);
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            child[i] = 0;
        }
    } else if (mode == 2) {
        int hub = rnd.next(0, max(0, n / 3));
        for (int i = 1; i <= n; ++i) {
            if (i <= hub) {
                child[i] = rnd.next(0, i - 1);
            } else if (rnd.next(100) < 70) {
                child[i] = hub;
            } else {
                child[i] = rnd.next(0, i - 1);
            }
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            if (i == 1 || rnd.next(100) < 75) {
                child[i] = i - 1;
            } else {
                child[i] = rnd.next(0, i - 1);
            }
        }
    } else if (mode == 4) {
        vector<int> frontier(1, 0);
        int nextNode = 1;
        while (nextNode <= n && !frontier.empty()) {
            int parent = frontier.front();
            frontier.erase(frontier.begin());
            int remaining = n - nextNode + 1;
            int maxChildren = min(remaining, d + rnd.next(0, d + 2));
            int count = rnd.next(1, maxChildren);
            for (int j = 0; j < count && nextNode <= n; ++j) {
                child[nextNode] = parent;
                frontier.push_back(nextNode);
                ++nextNode;
            }
        }
        while (nextNode <= n) {
            child[nextNode] = rnd.next(0, nextNode - 1);
            ++nextNode;
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        for (int rank = 0; rank < n; ++rank) {
            int alien = order[rank];
            if (rank == 0) {
                child[alien] = 0;
            } else if (rnd.next(100) < 85) {
                child[alien] = order[rnd.next(0, rank - 1)];
            } else {
                child[alien] = 0;
            }
        }
    }

    println(n, d);
    vector<int> output;
    output.reserve(n);
    for (int i = 1; i <= n; ++i) {
        output.push_back(child[i]);
    }
    println(output);

    return 0;
}
