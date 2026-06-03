#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);
    if (mode == 1) {
        n = 1;
    } else if (mode == 2) {
        m = 1;
    } else if (mode == 5) {
        n = rnd.next(8, 14);
        m = rnd.next(8, 14);
    }

    int winner = rnd.next(1, n);
    int turn = rnd.next(1, m);
    if (mode == 3) {
        winner = 1;
        turn = 1;
    } else if (mode == 4) {
        winner = n;
        turn = m;
    }

    int prefixLimit = max(1, turn - 1);
    int base = rnd.next(1, 30);
    int k = rnd.next(base * prefixLimit + 1, base * prefixLimit + 80);
    if (mode == 3) {
        k = rnd.next(1, 10);
    } else if (mode == 4) {
        k = rnd.next(200, 500);
    }

    vector<vector<int>> a(n, vector<int>(m, 1));
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            int value = rnd.next(1, base);
            if (j + 1 < turn || (j + 1 == turn && i + 1 < winner)) {
                value = min(value, max(1, k - 1 - sum));
            }
            a[i][j] = value;
            sum += value;
        }
    }

    int beforeWinner = 0;
    for (int j = 0; j + 1 < turn; ++j) {
        beforeWinner += a[winner - 1][j];
    }
    a[winner - 1][turn - 1] = max(1, k - beforeWinner);

    if (mode == 0 && winner < n) {
        int other = rnd.next(winner + 1, n);
        int beforeOther = 0;
        for (int j = 0; j + 1 < turn; ++j) {
            beforeOther += a[other - 1][j];
        }
        a[other - 1][turn - 1] = max(a[other - 1][turn - 1], k - beforeOther);
    }

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
