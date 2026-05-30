#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    for (int i = 1; i <= N; ++i) {
        setTestCase(i);

        inf.readInt(0, i - 1, "A_i");
        inf.readSpace();
        inf.readInt(0, i - 1, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
