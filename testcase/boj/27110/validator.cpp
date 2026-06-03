#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "N");
    inf.readEoln();

    inf.readInt(1, 3000, "A");
    inf.readSpace();
    inf.readInt(1, 3000, "B");
    inf.readSpace();
    inf.readInt(1, 3000, "C");
    inf.readEoln();

    inf.readEof();
}
