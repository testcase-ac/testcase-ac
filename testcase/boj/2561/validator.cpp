#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(5, 1000, "N");
    inf.readEoln();

    // 2. Read the permutation
    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // 3. Check that a is a permutation of 1..N
    set<int> seen;
    for (int i = 0; i < N; ++i) {
        ensuref(seen.insert(a[i]).second, "Duplicate value %d found at position %d", a[i], i+1);
    }
    // No need to check for missing values, as range is enforced and all are unique

    inf.readEof();
}
