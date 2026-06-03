#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,1000000}", "message");
    inf.readEoln();
    inf.readEof();
}
