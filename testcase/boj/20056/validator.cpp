#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size N, number of fireballs M, and number of moves K
    int N = inf.readInt(4, 50, "N");
    inf.readSpace();
    // M can be at most N*N
    int M = inf.readInt(0, (long long)N * N, "M");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Ensure initial positions are distinct
    set<pair<int,int>> seen;
    for (int i = 0; i < M; i++) {
        int r = inf.readInt(1, N, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, N, "c_i");
        inf.readSpace();
        int m = inf.readInt(1, 1000, "m_i");
        inf.readSpace();
        int s = inf.readInt(1, 1000, "s_i");
        inf.readSpace();
        int d = inf.readInt(0, 7, "d_i");
        inf.readEoln();

        // No two fireballs start at the same cell
        ensuref(!seen.count({r, c}),
                "Duplicate initial position at fireball %d: (%d, %d)",
                i, r, c);
        seen.insert({r, c});
    }

    inf.readEof();
    return 0;
}
