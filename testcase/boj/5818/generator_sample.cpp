#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 4) {
        n = rnd.next(10, 18);
    } else {
        n = rnd.next(3, 10);
    }

    vector<vector<int>> cost(n, vector<int>(n, 0));
    vector<int> group(n);
    int groups = rnd.next(1, min(n, 4));
    for (int i = 0; i < n; ++i) {
        group[i] = rnd.next(0, groups - 1);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int value;
            if (mode == 0) {
                value = rnd.any(vector<int>{1, 2, 999999, 1000000});
            } else if (mode == 1) {
                value = rnd.next(1, 30);
            } else if (mode == 2) {
                int base = (group[i] == group[j] ? rnd.next(1, 12) : rnd.next(40, 140));
                value = base + rnd.next(0, 8);
            } else if (mode == 3) {
                int hubBias = (i == 0 || j == 0 ? rnd.next(1, 20) : rnd.next(60, 220));
                value = hubBias;
            } else {
                value = rnd.next(1, 1000000);
            }
            cost[i][j] = cost[j][i] = value;
        }
    }

    vector<int> assign(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            assign[i] = rnd.any(vector<int>{1, 2, 999999, 1000000});
        } else if (mode == 3 && i == 0) {
            assign[i] = rnd.next(1, 15);
        } else if (mode == 4) {
            assign[i] = rnd.next(1, 1000000);
        } else {
            assign[i] = rnd.next(1, 80);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(cost[i]);
    }
    println(assign);

    return 0;
}
