#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int b = inf.readInt(1100, 9900, "B");
    inf.readEoln();

    ensuref(b % 11 == 0, "B must be divisible by 11: %d", b);

    inf.readEof();
}
