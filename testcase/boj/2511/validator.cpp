#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A's cards
    vector<int> A = inf.readInts(10, 0, 9, "A_i");
    inf.readEoln();
    // Check that A is a permutation of 0..9
    {
        vector<bool> seen(10, false);
        for (int i = 0; i < 10; i++) {
            int x = A[i];
            ensuref(!seen[x],
                    "Duplicate number in A at position %d: %d", i+1, x);
            seen[x] = true;
        }
        for (int x = 0; x < 10; x++) {
            ensuref(seen[x],
                    "Missing number in A: %d", x);
        }
    }

    // Second line: B's cards
    vector<int> B = inf.readInts(10, 0, 9, "B_i");
    inf.readEoln();
    // Check that B is a permutation of 0..9
    {
        vector<bool> seen(10, false);
        for (int i = 0; i < 10; i++) {
            int x = B[i];
            ensuref(!seen[x],
                    "Duplicate number in B at position %d: %d", i+1, x);
            seen[x] = true;
        }
        for (int x = 0; x < 10; x++) {
            ensuref(seen[x],
                    "Missing number in B: %d", x);
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
