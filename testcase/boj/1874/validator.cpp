#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read the sequence and check it's a permutation of 1..n
    vector<bool> seen(n+1, false);
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(1, n, "a_i");
        inf.readEoln();
        ensuref(!seen[x],
                "Duplicate number at position %d: %d", i+1, x);
        seen[x] = true;
    }

    // No extra data
    inf.readEof();
    return 0;
}
