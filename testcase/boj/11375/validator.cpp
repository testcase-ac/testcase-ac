#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int k = inf.readInt(0, m, "k_" + to_string(i));
        for (int j = 1; j <= k; ++j) {
            inf.readSpace();
            inf.readInt(1, m, "job_" + to_string(i) + "_" + to_string(j));
        }
        inf.readEoln();
    }

    inf.readEof();
}
