#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[0-9]+", "N");
    inf.readEoln();
    inf.readEof();

    ensuref(n[0] != '0', "N must not start with 0");

    const string maxN = "10000000000000000";
    ensuref(n.size() < maxN.size() || (n.size() == maxN.size() && n <= maxN),
            "N must be at most 10^16");

    return 0;
}
