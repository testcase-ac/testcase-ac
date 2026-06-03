#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,50}", "S");
    ensuref((int)s.size() == n, "S length must be N: N=%d, length=%d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
