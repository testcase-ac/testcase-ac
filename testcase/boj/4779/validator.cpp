#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int line_count = 0;
    while (!inf.eof()) {
        ++line_count;
        inf.readInt(0, 12, "N");
        inf.readEoln();
    }

    ensuref(line_count > 0, "input must contain at least one value");
    inf.readEof();
}
