#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 600, "N");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "H_i");
    inf.readEoln();

    inf.readEof();
}
