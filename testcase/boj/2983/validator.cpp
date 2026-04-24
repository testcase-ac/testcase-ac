#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read directions string
    string dirs = inf.readToken("[ABCD]+", "dirs");
    ensuref((int)dirs.length() == K,
            "Length of dirs (%d) does not match K (%d)", (int)dirs.length(), K);
    inf.readEoln();

    // Read plant coordinates and ensure uniqueness
    set<pair<int,int>> plants;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();
        pair<int,int> p = {x, y};
        ensuref(!plants.count(p),
                "Duplicate plant detected at index %d: (%d, %d)", i, x, y);
        plants.insert(p);
    }

    inf.readEof();
    return 0;
}
