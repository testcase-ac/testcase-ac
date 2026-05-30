#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static void readSegment(const char* leftName, const char* rightName, int index) {
    int left = inf.readInt(1, 1000000000, leftName);
    inf.readSpace();
    int right = inf.readInt(1, 1000000000, rightName);
    inf.readEoln();
    ensuref(left <= right, "segment %d must satisfy left <= right", index);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        readSegment("X_i", "Y_i", i + 1);
    }

    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        readSegment("Z_i", "W_i", i + 1);
    }

    inf.readEof();
}
