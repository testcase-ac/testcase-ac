#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string oct = inf.readToken("[0-7]+", "octal");
    ensuref(oct.size() >= 1 && oct.size() <= 333334,
            "octal length must be between 1 and 333334, got %zu", oct.size());
    ensuref(oct == "0" || oct[0] != '0',
            "nonzero octal numbers must not have leading zeroes");

    inf.readEoln();
    inf.readEof();
}
