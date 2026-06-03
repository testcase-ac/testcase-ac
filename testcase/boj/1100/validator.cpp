#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 8; ++i) {
        inf.readLine("[.F]{8}", "row");
    }

    inf.readEof();
}
