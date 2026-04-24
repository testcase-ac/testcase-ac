#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000, "L");
    inf.readEoln();

    set<pair<int,int>> pts;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-10000, 10000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "Y_i");
        inf.readEoln();

        // Ensure all points are distinct
        pair<int,int> p = {x, y};
        ensuref(!pts.count(p),
                "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        pts.insert(p);
    }

    inf.readEof();
    return 0;
}
