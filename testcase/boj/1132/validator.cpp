#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<bool> appearsFirst(10, false);
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[A-J]{1,12}", "number");
        inf.readEoln();
        appearsFirst[s[0] - 'A'] = true;
    }

    bool hasZeroCandidate = false;
    for (bool first : appearsFirst) {
        if (!first) {
            hasZeroCandidate = true;
            break;
        }
    }
    ensuref(hasZeroCandidate, "at least one letter from A to J must never appear first");

    inf.readEof();
}
