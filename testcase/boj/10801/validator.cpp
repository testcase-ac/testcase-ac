#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read A's cards: exactly 10 integers between 1 and 10
    vector<int> a = inf.readInts(10, 1, 10, "a_i");
    inf.readEoln();
    // Read B's cards: exactly 10 integers between 1 and 10
    vector<int> b = inf.readInts(10, 1, 10, "b_i");
    inf.readEoln();

    // Check that A's cards form a permutation of 1..10
    {
        vector<bool> seen(11, false);
        for (int i = 0; i < 10; i++) {
            int v = a[i];
            ensuref(!seen[v],
                    "Duplicate card %d in A's hand at position %d", v, i + 1);
            seen[v] = true;
        }
        for (int v = 1; v <= 10; v++) {
            ensuref(seen[v], "Missing card %d in A's hand", v);
        }
    }
    // Check that B's cards form a permutation of 1..10
    {
        vector<bool> seen(11, false);
        for (int i = 0; i < 10; i++) {
            int v = b[i];
            ensuref(!seen[v],
                    "Duplicate card %d in B's hand at position %d", v, i + 1);
            seen[v] = true;
        }
        for (int v = 1; v <= 10; v++) {
            ensuref(seen[v], "Missing card %d in B's hand", v);
        }
    }

    inf.readEof();
    return 0;
}
