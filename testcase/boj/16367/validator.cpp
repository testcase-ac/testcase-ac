#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k and n
    int k = inf.readInt(4, 5000, "k");
    inf.readSpace();
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Each of the n participants provides exactly three distinct lamps with guessed colors
    for (int i = 0; i < n; i++) {
        int l1 = inf.readInt(1, k, "l1");
        inf.readSpace();
        inf.readToken("B|R", "c1");
        inf.readSpace();
        int l2 = inf.readInt(1, k, "l2");
        inf.readSpace();
        inf.readToken("B|R", "c2");
        inf.readSpace();
        int l3 = inf.readInt(1, k, "l3");
        inf.readSpace();
        inf.readToken("B|R", "c3");
        inf.readEoln();

        // Lamps must be distinct in each guess
        ensuref(l1 != l2 && l1 != l3 && l2 != l3,
                "Duplicate lamp in participant %d: %d, %d, %d", i + 1, l1, l2, l3);
    }

    inf.readEof();
    return 0;
}
