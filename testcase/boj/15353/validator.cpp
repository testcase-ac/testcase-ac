#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static string readPositiveBigInt(const char* name) {
    string value = inf.readToken("[0-9]{1,10000}", name);
    ensuref(value[0] != '0', "%s must be positive and canonical", name);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readPositiveBigInt("A");
    inf.readSpace();
    readPositiveBigInt("B");
    inf.readEoln();
    inf.readEof();
}
