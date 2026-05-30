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

    // CHECK: The statement says n is positive but gives no upper bound.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);
        inf.readInt(1, 1000000, "a");
        readOneOrMoreSpaces();
        inf.readInt(1, 1000000, "b");
        inf.readEoln();
    }

    inf.readEof();
}
