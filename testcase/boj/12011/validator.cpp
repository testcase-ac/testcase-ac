#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of cows
    int N = inf.readInt(3, 50000, "N");
    inf.readEoln();

    // Read cow positions and ensure distinctness
    set<pair<int,int>> coords;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 1000000000, "y_i");
        inf.readEoln();

        pair<int,int> p = make_pair(x, y);
        ensuref(!coords.count(p),
                "Duplicate cow position at index %d: (%d, %d)", i, x, y);
        coords.insert(p);
    }

    inf.readEof();
    return 0;
}
