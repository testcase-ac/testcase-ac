#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int row = 0; row < 10; ++row) {
        inf.readLine("[#O]{10}", format("row_%d", row + 1).c_str());
    }

    inf.readEof();
}
