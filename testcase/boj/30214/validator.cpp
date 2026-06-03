#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s1 = inf.readInt(0, 100, "s_1");
    inf.readSpace();
    int s2 = inf.readInt(1, 100, "s_2");
    inf.readEoln();

    ensuref(s1 <= s2, "s_1 must be at most s_2: %d > %d", s1, s2);

    inf.readEof();
}
