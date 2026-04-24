#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the N distinct values
    vector<int> a = inf.readInts(N, 1, 1000, "a_i");
    inf.readEoln();

    // Check distinctness
    {
        set<int> seen;
        for (int i = 0; i < N; i++) {
            bool inserted = seen.insert(a[i]).second;
            ensuref(inserted,
                    "Duplicate value detected at index %d: %d", i, a[i]);
        }
    }

    // No more input
    inf.readEof();
    return 0;
}
