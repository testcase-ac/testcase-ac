#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(5);
    int costMode = rnd.next(5);
    int n = (shape == 0 ? 1 : rnd.next(2, 35));

    vector<int> order;
    for (int node = 2; node <= n; ++node) {
        order.push_back(node);
    }
    if (shape >= 3) {
        shuffle(order.begin(), order.end());
    }

    vector<int> parent(n + 1, 1);
    vector<long long> edgeCost(n + 1, 0);
    vector<long long> dist(n + 1, 0);
    vector<int> attached(1, 1);

    for (int idx = 0; idx < static_cast<int>(order.size()); ++idx) {
        int node = order[idx];
        int p = 1;
        if (shape == 1) {
            p = 1;
        } else if (shape == 2) {
            p = attached.back();
        } else if (shape == 3) {
            p = rnd.any(attached);
        } else {
            int bias = rnd.next(3);
            if (bias == 0) {
                p = 1;
            } else if (bias == 1) {
                p = attached.back();
            } else {
                p = rnd.any(attached);
            }
        }

        long long c = 0;
        if (costMode == 0) {
            c = 0;
        } else if (costMode == 1) {
            c = rnd.next(0, 5);
        } else if (costMode == 2) {
            c = rnd.next(900000000, 1000000000);
        } else if (costMode == 3) {
            c = rnd.next(0, 1000000000);
        } else {
            c = (rnd.next(4) == 0 ? 0 : rnd.next(1, 1000));
        }

        parent[node] = p;
        edgeCost[node] = c;
        dist[node] = dist[p] + c;
        attached.push_back(node);
    }

    vector<long long> a(n + 1, 1);
    for (int node = 1; node <= n; ++node) {
        int mode = rnd.next(6);
        long long value = 1;
        if (mode == 0) {
            value = 1;
        } else if (mode == 1) {
            value = 1000000000LL;
        } else if (mode == 2) {
            value = max(1LL, min(1000000000LL, dist[node]));
        } else if (mode == 3) {
            value = min(1000000000LL, dist[node] + rnd.next(0, 20));
        } else if (mode == 4) {
            long long drop = rnd.next(0, 20);
            value = max(1LL, min(1000000000LL, dist[node]) - drop);
        } else {
            value = rnd.next(1, 1000000000);
        }
        a[node] = max(1LL, min(1000000000LL, value));
    }

    println(n);
    println(vector<long long>(a.begin() + 1, a.end()));
    for (int node = 2; node <= n; ++node) {
        println(parent[node], edgeCost[node]);
    }

    return 0;
}
