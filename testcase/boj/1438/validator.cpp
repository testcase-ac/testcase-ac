#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: even, 2 <= N <= 100
    int N = inf.readInt(2, 100, "N");
    ensuref(N % 2 == 0, "N must be even, but got %d", N);
    inf.readEoln();

    // Read N distinct points with 0 <= x,y <= 10000
    set<pair<int,int>> pts;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(0, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 10000, "y_i");
        inf.readEoln();
        pair<int,int> p = make_pair(x, y);
        ensuref(!pts.count(p),
                "Duplicate point at index %d: (%d, %d)", i, x, y);
        pts.insert(p);
    }

    inf.readEof();
    return 0;
}
