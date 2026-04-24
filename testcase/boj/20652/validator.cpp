#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cows
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // To ensure all x and y are unique
    set<int> seenX, seenY;

    for (int i = 0; i < N; i++) {
        // Direction: exactly 'N' or 'E'
        string dir = inf.readToken("[NE]", "dir");
        inf.readSpace();
        // Coordinates: 0 <= x,y <= 1e9
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();

        // Check uniqueness of x and y
        ensuref(!seenX.count(x),
                "Duplicate x-coordinate %d at cow index %d", x, i+1);
        ensuref(!seenY.count(y),
                "Duplicate y-coordinate %d at cow index %d", y, i+1);

        seenX.insert(x);
        seenY.insert(y);
    }

    // No extra characters or lines
    inf.readEof();
    return 0;
}
