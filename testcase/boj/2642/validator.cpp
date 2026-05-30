#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int rows = 6;
    const int cols = 6;
    array<int, 7> count{};

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int cell = inf.readInt(0, 6, "cell");
            ++count[cell];
            if (c + 1 < cols) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    for (int value = 1; value <= 6; ++value) {
        ensuref(count[value] == 1,
                "face label %d appears %d times, expected once",
                value, count[value]);
    }

    inf.readEof();
}
