#include "testlib.h"
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 15000, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 10000000, "M");
    inf.readEoln();

    // Read the N material numbers
    vector<int> a = inf.readInts(N, 1, 100000, "a_i");
    inf.readEoln();

    // Check that all material numbers are unique, as each material has a unique identifier
    unordered_set<int> seen;
    seen.reserve(N);
    for (int i = 0; i < N; i++) {
        int v = a[i];
        auto res = seen.insert(v);
        ensuref(res.second, "Duplicate material number detected at position %d: %d", i, v);
    }

    inf.readEof();
    return 0;
}
