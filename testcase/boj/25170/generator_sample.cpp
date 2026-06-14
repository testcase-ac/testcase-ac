#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 3);
        m = rnd.next(8, 16);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (mode == 2) {
        n = rnd.next(5, 10);
        m = n + rnd.next(-2, 2);
        m = max(2, min(12, m));
    } else if (mode == 3) {
        n = rnd.next(8, 14);
        m = rnd.next(8, 14);
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    }

    int minT = n + m - 1;
    int tBudget;
    if (mode == 0) {
        tBudget = rnd.next(minT, min(500, minT + 3));
    } else if (mode == 1) {
        tBudget = rnd.next(minT, min(500, minT + 20));
    } else if (mode == 2) {
        tBudget = rnd.next(minT, min(500, minT + 60));
    } else if (mode == 3) {
        tBudget = rnd.next(max(minT, 120), min(500, max(minT, 120) + 160));
    } else {
        tBudget = rnd.next(minT, 500);
    }

    vector<vector<int>> w(n, vector<int>(m));
    vector<vector<int>> cost(n, vector<int>(m));

    int weightCap = rnd.next(8, 100);
    int costCap = rnd.next(5, 100);
    int zeroCostChance = rnd.next(0, 20);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i == 0 && j == 0) || (i == n - 1 && j == m - 1)) {
                w[i][j] = 0;
            } else if (mode == 0) {
                w[i][j] = rnd.next(0, 15);
            } else if (mode == 2 && i == j) {
                w[i][j] = rnd.next(50, 100);
            } else if (mode == 3 && (i + j) % 3 == 0) {
                w[i][j] = rnd.next(60, 100);
            } else {
                w[i][j] = rnd.next(0, weightCap);
            }

            if (rnd.next(0, 99) < zeroCostChance) {
                cost[i][j] = 0;
            } else if (mode == 0) {
                cost[i][j] = rnd.next(0, 8);
            } else if (mode == 1) {
                cost[i][j] = rnd.next(1, 30);
            } else if (mode == 3 && (i + j) % 4 == 0) {
                cost[i][j] = rnd.next(40, 100);
            } else {
                cost[i][j] = rnd.next(0, costCap);
            }
        }
    }

    println(n, m, tBudget);
    for (int i = 0; i < n; ++i) {
        println(w[i]);
    }
    for (int i = 0; i < n; ++i) {
        println(cost[i]);
    }

    return 0;
}
