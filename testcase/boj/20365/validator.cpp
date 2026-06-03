#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    string colors = inf.readLine("[RB]{1,500000}", "colors");
    ensuref((int)colors.size() == n, "colors length is %d, expected %d", (int)colors.size(), n);

    inf.readEof();
}
