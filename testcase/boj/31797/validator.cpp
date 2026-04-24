#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read the hand heights and ensure all are distinct
    set<int> heights;
    for (int i = 1; i <= M; i++) {
        int h1 = inf.readInt(1, 10000, "H1_i");
        inf.readSpace();
        int h2 = inf.readInt(1, 10000, "H2_i");
        inf.readEoln();

        // No two hands can have the same height
        ensuref(heights.insert(h1).second,
                "Duplicate hand height detected: %d", h1);
        ensuref(heights.insert(h2).second,
                "Duplicate hand height detected: %d", h2);
    }

    inf.readEof();
    return 0;
}
