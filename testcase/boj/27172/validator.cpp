#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read x_1 ... x_N
    vector<int> x = inf.readInts(N, 1, 1000000, "x_i");
    inf.readEoln();

    // Check all x_i are unique
    set<int> seen;
    for (int i = 0; i < N; ++i) {
        ensuref(seen.insert(x[i]).second, "Duplicate x_i detected at index %d: %d", i+1, x[i]);
    }

    inf.readEof();
}
