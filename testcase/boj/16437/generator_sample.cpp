#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 24 : 14);

    vector<int> parent(n + 1, 1);

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) parent[i] = 1;
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) parent[i] = i - 1;
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) parent[i] = i / 2;
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) parent[i] = rnd.next(1, i - 1);
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin() + 1, order.end());

        vector<int> baseParent(n + 1, 1);
        for (int depth = 1; depth < n; ++depth) {
            int child = order[depth];
            int par = order[rnd.next(0, depth - 1)];
            baseParent[child] = par;
        }
        parent = baseParent;
    }

    vector<char> type(n + 1, 'S');
    vector<long long> amount(n + 1, 1);
    int valueMode = rnd.next(0, 4);
    for (int i = 2; i <= n; ++i) {
        if (mode == 1) {
            type[i] = (i % 2 == 0 ? 'S' : 'W');
        } else if (mode == 0) {
            type[i] = (rnd.next(0, 3) == 0 ? 'W' : 'S');
        } else {
            type[i] = (rnd.next(0, 1) == 0 ? 'S' : 'W');
        }

        if (valueMode == 0) {
            amount[i] = rnd.next(1, 20);
        } else if (valueMode == 1) {
            amount[i] = rnd.next(1, 1000);
        } else if (valueMode == 2) {
            amount[i] = rnd.next(900000000, 1000000000);
        } else if (type[i] == 'W') {
            amount[i] = rnd.next(1, 200);
        } else {
            amount[i] = rnd.next(50, 500);
        }
    }

    if (rnd.next(0, 4) == 0) {
        int idx = rnd.next(2, n);
        amount[idx] = 1000000000LL;
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        println(type[i], amount[i], parent[i]);
    }

    return 0;
}
