#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cows
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Track used x and y coordinates
    set<int> xs, ys;

    for (int i = 1; i <= N; i++) {
        // Direction: 'N' or 'E'
        string dir = inf.readToken("[NE]", "dir");
        inf.readSpace();

        // Coordinates
        int x = inf.readInt(0, 1000000000, "x");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y");
        inf.readEoln();

        // Uniqueness constraints
        ensuref(!xs.count(x),
                "Duplicate x-coordinate %d for cow %d", x, i);
        xs.insert(x);
        ensuref(!ys.count(y),
                "Duplicate y-coordinate %d for cow %d", y, i);
        ys.insert(y);
    }

    inf.readEof();
    return 0;
}
