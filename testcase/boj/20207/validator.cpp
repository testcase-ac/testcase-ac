#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int s = inf.readInt(1, 365, "S");
        inf.readSpace();
        int e = inf.readInt(s, 365, "E");
        inf.readEoln();
    }

    inf.readEof();
}
