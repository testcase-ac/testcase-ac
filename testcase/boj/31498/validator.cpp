#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000LL, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readEoln();

    inf.readLong(0LL, 1000000000000LL, "C");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    inf.readLong(0LL, b, "K");
    inf.readEoln();
    inf.readEof();
}
