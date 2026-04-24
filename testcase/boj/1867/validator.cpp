#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "k");
    inf.readEoln();

    // Read k distinct stone positions
    set<pair<int,int>> stones;
    for (int i = 0; i < k; i++) {
        int r = inf.readInt(1, n, "row");
        inf.readSpace();
        int c = inf.readInt(1, n, "col");
        inf.readEoln();

        bool inserted = stones.insert({r, c}).second;
        ensuref(inserted,
                "Duplicate stone detected at position (%d, %d)", r, c);
    }

    inf.readEof();
    return 0;
}
