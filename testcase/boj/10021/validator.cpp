#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    // Read N points, check bounds and uniqueness
    set<pair<int, int>> seen;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(0, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "y_i");
        inf.readEoln();
        ensuref(seen.count({x, y}) == 0, "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        seen.insert({x, y});
    }

    inf.readEof();
}
