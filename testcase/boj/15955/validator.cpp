#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 250000, "Q");
    inf.readEoln();

    // Read N distinct checkpoints
    set<pair<int,int>> pts;
    pts.clear();
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y_i");
        inf.readEoln();

        pair<int,int> p = make_pair(x, y);
        ensuref(!pts.count(p),
                "Duplicate checkpoint at index %d: (%d, %d)", i, x, y);
        pts.insert(p);
    }

    // Read Q queries
    for (int i = 1; i <= Q; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int X = inf.readInt(0, 1000000000, "X_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
