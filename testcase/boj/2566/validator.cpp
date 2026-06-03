#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int row = 1; row <= 9; ++row) {
        for (int col = 1; col <= 9; ++col) {
            inf.readInt(0, 99, "a");
            if (col == 9) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
