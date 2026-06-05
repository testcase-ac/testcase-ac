#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);

    vector<pair<int, int>> edges;
    vector<int> depth(n, 0);
    for (int c = 1; c < n; ++c) {
        int p;
        if (mode == 0) {
            p = c - 1;
        } else if (mode == 1) {
            p = 0;
        } else if (mode == 2) {
            p = (c - 1) / 2;
        } else if (mode == 3) {
            p = rnd.next(0, c - 1);
        } else {
            int spine = max(1, n / 2);
            p = (c < spine ? c - 1 : rnd.next(0, spine - 1));
        }
        edges.push_back({p, c});
        depth[c] = depth[p] + 1;
    }

    vector<pair<int, int>> cost(n);
    int costMode = rnd.next(5);
    for (int i = 0; i < n; ++i) {
        int w;
        int b;
        if (costMode == 0) {
            w = rnd.next(1, 30);
            b = rnd.next(1, 30);
        } else if (costMode == 1) {
            int low = rnd.next(1, 5);
            int high = rnd.next(50000, 100000);
            if (depth[i] % 2 == 0) {
                w = low;
                b = high;
            } else {
                w = high;
                b = low;
            }
        } else if (costMode == 2) {
            int low = rnd.next(1, 5);
            int high = rnd.next(50000, 100000);
            if (depth[i] % 2 == 0) {
                w = high;
                b = low;
            } else {
                w = low;
                b = high;
            }
        } else if (costMode == 3) {
            int same = rnd.next(1, 100000);
            w = same;
            b = same;
        } else {
            w = rnd.any(vector<int>{1, 2, 99999, 100000});
            b = rnd.any(vector<int>{1, 3, 99998, 100000});
        }
        cost[i] = {w, b};
    }

    println(n);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }
    for (auto item : cost) {
        println(item.first, item.second);
    }

    return 0;
}
