#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of buildings
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // To ensure all building coordinates are unique
    set<pair<int,int>> coords;

    for (int i = 0; i < N; i++) {
        // Read x and y
        int x = inf.readInt(-1000000, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y_i");
        inf.readEoln();

        // No building on the x-axis
        ensuref(y != 0, "Building %d has y = 0, but no building may lie on the x-axis", i+1);

        // Coordinates must be distinct
        pair<int,int> p = make_pair(x, y);
        ensuref(!coords.count(p),
                "Duplicate building coordinates at index %d: (%d, %d)", i+1, x, y);
        coords.insert(p);
    }

    // No extra content after the last line
    inf.readEof();
    return 0;
}
