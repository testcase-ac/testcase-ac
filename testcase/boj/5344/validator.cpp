#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

void readOneOrMoreSpaces() {
    inf.readSpace();
    while (inf.curChar() == ' ') {
        inf.readSpace();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for n.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);

        long long a = inf.readLong(1, 1000000000000000000LL, "a");
        readOneOrMoreSpaces();
        long long b = inf.readLong(1, 1000000000000000000LL, "b");
        inf.readEoln();
    }

    inf.readEof();
}
