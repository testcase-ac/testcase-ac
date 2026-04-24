#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the nine distinct hat numbers, each on its own line.
    vector<int> h(9);
    for (int i = 0; i < 9; i++) {
        char name[16];
        sprintf(name, "h%d", i+1);
        h[i] = inf.readInt(1, 99, name);
        inf.readEoln();
    }

    // Check all numbers are distinct.
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9; j++) {
            ensuref(h[i] != h[j],
                    "Duplicate heights detected at indices %d and %d: both are %d",
                    i+1, j+1, h[i]);
        }
    }

    // The problem guarantees exactly one subset of 7 out of 9 that sums to 100.
    // Equivalently, exactly one pair of dwarves (i,j) to exclude so that the
    // sum of the remaining 7 is 100.
    int total = 0;
    for (int x : h) total += x;

    int count_pairs = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9; j++) {
            if (total - h[i] - h[j] == 100) {
                count_pairs++;
            }
        }
    }
    ensuref(count_pairs == 1,
            "There must be exactly one unique solution, but found %d valid exclusion pairs",
            count_pairs);

    inf.readEof();
    return 0;
}
