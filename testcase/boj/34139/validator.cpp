#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H and N
    int H = inf.readInt(1, 1000000000, "H");
    inf.readSpace();
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 0; i < N; ++i) {
        int r = inf.readInt(1, H, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000000000, "c_i");
        inf.readEoln();

        auto pos = make_pair(r, c);
        ensuref(positions.count(pos) == 0,
            "Duplicate starting position found at index %d: (%d, %d)", i+1, r, c);
        positions.insert(pos);
    }

    inf.readEof();
}
