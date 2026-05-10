#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M, N, K
    int M = inf.readInt(2, 100000, "M");
    inf.readSpace();
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 200000, "K");
    inf.readEoln();

    set<pair<int,int>> switches;
    for (int i = 0; i < K; ++i) {
        int x = inf.readInt(1, M, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readEoln();

        auto p = make_pair(x, y);
        ensuref(switches.count(p) == 0, "Duplicate switch at (%d, %d) (index %d)", x, y, i+1);
        switches.insert(p);
    }

    inf.readEof();
}
