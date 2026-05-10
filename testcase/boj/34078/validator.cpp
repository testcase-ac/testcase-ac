#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    // 2. Read a_1 ... a_N
    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // 3. Check all a_i are distinct and form a permutation of 1..N
    vector<bool> seen(N+1, false);
    for (int i = 0; i < N; ++i) {
        int val = a[i];
        ensuref(!seen[val], "a_i is not unique: value %d appears more than once", val);
        seen[val] = true;
    }
    // (No need to check for missing values, as all a_i in [1,N] and unique)

    inf.readEof();
}
