#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, l, M
    int N = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int l = inf.readInt(4, 100, "l");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Validate additional constraints on l
    ensuref(l % 2 == 0, "l must be even, but got %d", l);
    long long maxL = 4LL * N - 4;
    ensuref(l <= maxL, "l must satisfy l <= 4*N-4, but got l=%d, 4*N-4=%lld", l, maxL);

    // Read fish positions and ensure distinctness
    set<pair<int,int>> fishes;
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readEoln();

        pair<int,int> p = make_pair(x, y);
        ensuref(!fishes.count(p),
                "Duplicate fish at position (%d, %d)", x, y);
        fishes.insert(p);
    }

    inf.readEof();
    return 0;
}
