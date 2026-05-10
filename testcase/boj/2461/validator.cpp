#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read abilities
    // Ability: integer in [0, 1e9], and globally all abilities are distinct.
    // Also, by problem statement, each class has exactly M students.
    int total = N * M;
    vector<long long> allVals;
    allVals.reserve(total);

    for (int i = 0; i < N; ++i) {
        vector<long long> row = inf.readLongs(M, 0LL, 1000000000LL, "a_ij");
        inf.readEoln();
        for (int j = 0; j < M; ++j) {
            allVals.push_back(row[j]);
        }
    }

    // Check all abilities are globally distinct
    sort(allVals.begin(), allVals.end());
    for (int i = 1; i < (int)allVals.size(); ++i) {
        ensuref(allVals[i] != allVals[i - 1],
                "All ability values must be distinct, but value %lld appears at least twice.",
                allVals[i]);
    }

    inf.readEof();
}
