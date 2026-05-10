#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read D and N
    long long D = inf.readLong(1LL, 1000000000LL, "D");
    inf.readSpace();
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Store intervals and colors
    vector<long long> l(N), r(N);
    vector<int> c(N);

    set<long long> endpoints; // for checking valid endpoints

    for (int i = 0; i < N; ++i) {
        l[i] = inf.readLong(1LL, D, "l_i");
        inf.readSpace();
        r[i] = inf.readLong(l[i], D, "r_i");
        inf.readSpace();
        c[i] = inf.readInt(1, N, "c_i");
        inf.readEoln();

        // Optional: collect endpoints for further checks if needed
        endpoints.insert(l[i]);
        endpoints.insert(r[i]);
    }

    // No further global properties are implied by the problem statement.
    // - No restriction on overlapping intervals.
    // - No restriction on color uniqueness.
    // - No restriction on full coverage.
    // - No restriction on intervals being sorted or non-overlapping.

    inf.readEof();
}
