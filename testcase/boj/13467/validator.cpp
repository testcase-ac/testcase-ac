#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of beacons
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // To ensure no two beacons share the same coordinates
    set<pair<int,int>> seen;

    for (int i = 0; i < N; i++) {
        // Read beacon position and measured distance
        int x = inf.readInt(-1000000, 1000000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "Y_i");
        inf.readSpace();
        int d = inf.readInt(0, 4000000, "D_i");
        inf.readEoln();

        // Check for duplicate beacon coordinates
        pair<int,int> coord = make_pair(x, y);
        ensuref(!seen.count(coord),
                "Duplicate beacon position at index %d: (%d, %d)",
                i, x, y);
        seen.insert(coord);
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
