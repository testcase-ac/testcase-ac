#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20, "m");
    inf.readEoln();

    int coins = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[.o#]{1,20}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d", i + 1, (int)row.size(), m);
        for (char cell : row) {
            if (cell == 'o') {
                ++coins;
            }
        }
    }
    ensuref(coins == 2, "expected exactly 2 coins, found %d", coins);

    inf.readEof();
}
