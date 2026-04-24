#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(3, 1500, "N");
    inf.readEoln();

    // Read points and ensure uniqueness
    set<pair<int,int>> points;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y_i");
        inf.readEoln();

        pair<int,int> p = {x, y};
        ensuref(!points.count(p),
                "Duplicate point at line %d: (%d, %d)", i+2, x, y);
        points.insert(p);
    }

    inf.readEof();
    return 0;
}
