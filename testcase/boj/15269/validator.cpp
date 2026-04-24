#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of photos
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; i++) {
        // Read photo type: 'A' or 'B'
        string t = inf.readToken("[AB]", "type");
        inf.readSpace();

        // Read center coordinates
        int x = inf.readInt(-1000, 1000, "x");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "y");
        inf.readSpace();

        if (t == "A") {
            // Side length a_j: even, 2 <= a_j <= 1000
            int a = inf.readInt(2, 1000, "a");
            ensuref(a % 2 == 0,
                    "Photo %d: side length a=%d is not an even integer", i, a);
        } else {
            // Diagonal length d_j: even, 2 <= d_j <= 1000
            int d = inf.readInt(2, 1000, "d");
            ensuref(d % 2 == 0,
                    "Photo %d: diagonal length d=%d is not an even integer", i, d);
        }

        // End of this photo line
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
