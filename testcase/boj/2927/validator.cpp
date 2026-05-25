#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 1000, "penguins");
    inf.readEoln();

    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        string command = inf.readToken("bridge|penguins|excursion", "command");
        inf.readSpace();

        if (command == "bridge") {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            ensuref(a != b, "bridge command %d has equal islands: %d", i + 1, a);
        } else if (command == "penguins") {
            inf.readInt(1, n, "A");
            inf.readSpace();
            inf.readInt(0, 1000, "X");
        } else {
            inf.readInt(1, n, "A");
            inf.readSpace();
            inf.readInt(1, n, "B");
        }

        inf.readEoln();
    }

    inf.readEof();
}
