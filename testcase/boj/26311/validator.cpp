#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read array a: positive integers, 1 ≤ a_i ≤ 5000
    vector<int> a = inf.readInts(n, 1, 5000, "a_i");
    inf.readEoln();

    // Read array b: non-negative integers, 0 ≤ b_i ≤ 5000
    vector<int> b = inf.readInts(n, 0, 5000, "b_i");
    inf.readEoln();

    // Validate that for all i: b_i ≤ a_i
    for (int i = 0; i < n; i++) {
        ensuref(b[i] <= a[i],
                "Constraint violated at index %d: b_i (%d) must be <= a_i (%d)",
                i + 1, b[i], a[i]);
    }

    inf.readEof();
    return 0;
}
