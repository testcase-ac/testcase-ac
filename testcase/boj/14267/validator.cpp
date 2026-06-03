#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "m");
    inf.readEoln();

    int rootBoss = inf.readInt(-1, -1, "boss_1");
    (void)rootBoss;
    for (int employee = 2; employee <= n; ++employee) {
        inf.readSpace();
        inf.readInt(1, employee - 1, "boss_i");
    }
    inf.readEoln();

    for (int query = 1; query <= m; ++query) {
        int employee = inf.readInt(2, n, "i");
        (void)employee;
        inf.readSpace();
        inf.readInt(1, 1000, "w");
        inf.readEoln();
    }

    inf.readEof();
}
