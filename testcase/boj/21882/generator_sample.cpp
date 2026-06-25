#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 20);
    int treeMode = rnd.next(0, 5);
    vector<int> parent(n + 1);

    for (int i = 2; i <= n; ++i) {
        if (treeMode == 0) {
            parent[i] = i - 1;
        } else if (treeMode == 1) {
            parent[i] = 1;
        } else if (treeMode == 2) {
            parent[i] = i / 2;
        } else if (treeMode == 3) {
            int lo = max(1, i - 4);
            parent[i] = rnd.next(lo, i - 1);
        } else if (treeMode == 4) {
            parent[i] = rnd.wnext(i - 1, -2) + 1;
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
    }

    int coinMode = rnd.next(0, 5);
    vector<int> coins(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (coinMode == 0) {
            coins[i] = rnd.next(0, 1);
        } else if (coinMode == 1) {
            coins[i] = rnd.next() < 0.65 ? 0 : rnd.next(1, 9);
        } else if (coinMode == 2) {
            coins[i] = rnd.next(0, 20);
        } else if (coinMode == 3) {
            coins[i] = rnd.any(vector<int>{0, 1, 2, 99999, 100000});
        } else if (coinMode == 4) {
            coins[i] = (i == 1 || rnd.next() < 0.25) ? rnd.next(1, 100000) : 0;
        } else {
            coins[i] = rnd.next(0, 100000);
        }
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            printf(" ");
        }
        printf("%d", parent[i]);
    }
    printf("\n");

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            printf(" ");
        }
        printf("%d", coins[i]);
    }
    printf("\n");

    return 0;
}
