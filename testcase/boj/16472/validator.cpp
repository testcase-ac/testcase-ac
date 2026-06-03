#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 26, "n");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,100000}", "s");
    inf.readEoln();

    inf.readEof();
}
