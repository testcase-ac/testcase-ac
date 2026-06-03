#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 1000, "N");
    inf.readEoln();
    ensuref(n % 4 == 0, "N must be divisible by 4, got %d", n);

    inf.readEof();
}
