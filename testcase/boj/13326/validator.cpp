#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int n = inf.readInt(2, 5000, "n");
    inf.readEoln();

    // Read points and ensure they are distinct
    set<pair<int,int>> seen;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(0, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 10000, "y_i");
        inf.readEoln();
        pair<int,int> p = {x, y};
        ensuref(!seen.count(p),
                "Duplicate point at index %d: (%d, %d)",
                i+1, x, y);
        seen.insert(p);
    }

    inf.readEof();
    return 0;
}
