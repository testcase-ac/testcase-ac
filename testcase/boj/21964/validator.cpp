#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100000, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Za-z,.]{5,100000}", "S");
    ensuref((int)s.size() == n, "S length is %d, expected %d", (int)s.size(), n);
    inf.readEoln();

    inf.readEof();
}
