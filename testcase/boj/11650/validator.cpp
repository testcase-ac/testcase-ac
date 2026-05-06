#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read points and ensure no duplicates
    set<pair<int,int>> pts;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-100000, 100000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100000, 100000, "y_i");
        inf.readEoln();
        pair<int,int> p = {x, y};
        ensuref(!pts.count(p),
                "Duplicate point at index %d: (%d, %d)",
                i+1, x, y);
        pts.insert(p);
    }

    inf.readEof();
    return 0;
}
