#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of dice
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // For each dice, read 6 face values
    for (int i = 1; i <= n; i++) {
        // Read exactly 6 integers in [1,6], enforcing exactly one space between them
        vector<int> faces(6);
        for (int j = 0; j < 6; j++) {
            faces[j] = inf.readInt(1, 6, "face");
            if (j < 5) {
                inf.readSpace();
            }
        }
        inf.readEoln();

        // Check that faces form a permutation of 1..6
        // (each number 1 through 6 appears exactly once)
        bool seen[7] = { false };
        for (int x : faces) {
            ensuref(!seen[x],
                    "Dice %d: face value %d is repeated",
                    i, x);
            seen[x] = true;
        }
        for (int v = 1; v <= 6; v++) {
            ensuref(seen[v],
                    "Dice %d: missing face value %d",
                    i, v);
        }
    }

    inf.readEof();
    return 0;
}
