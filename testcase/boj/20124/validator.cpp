#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const long long MAXB = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    set<string> names;

    for (int i = 0; i < N; ++i) {
        // Read name: lowercase letters, length 1..10
        string name = inf.readToken("[a-z]{1,10}", "A_i");
        inf.readSpace();
        long long score = inf.readLong(1LL, MAXB, "B_i");
        inf.readEoln();

        // Names must be distinct
        ensuref(!names.count(name),
                "Duplicate name found at line %d: '%s'",
                i + 2, name.c_str());
        names.insert(name);
    }

    inf.readEof();
}
