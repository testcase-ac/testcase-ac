#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
Problem recap (for validator perspective):
- Single test case.
- First line: N M, both natural numbers (1..50).
- Next N lines: each exactly M characters.
- Characters allowed: '.', '#', '*'.
- Exactly one '*' in the entire grid.
- Geometry description: not our job to check visibility / answer, only structural constraints.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    int starCount = 0;

    for (int i = 0; i < N; ++i) {
        string row = inf.readLine("[.#*]{1,50}", "row");
        ensuref((int)row.size() == M,
                "Row %d has length %d but M = %d", i + 1, (int)row.size(), M);
        for (int j = 0; j < M; ++j) {
            char c = row[j];
            if (c == '*') {
                ++starCount;
            }
        }
    }

    ensuref(starCount == 1,
            "There must be exactly one light source '*', but found %d", starCount);

    inf.readEof();
}
