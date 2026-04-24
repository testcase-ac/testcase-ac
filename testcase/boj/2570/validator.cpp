#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board size N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read number of obstacles M
    // Logically, at most N*N obstacles can exist on an N x N board
    int maxOb = N * N;
    int M = inf.readInt(0, maxOb, "M");
    inf.readEoln();

    // Read obstacle positions and ensure they are within bounds and unique
    set<pair<int,int>> obs;
    for (int i = 1; i <= M; i++) {
        int r = inf.readInt(1, N, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, N, "c_i");
        inf.readEoln();
        pair<int,int> p = {r, c};
        ensuref(!obs.count(p),
                "Duplicate obstacle at index %d: (%d, %d)", i, r, c);
        obs.insert(p);
    }

    // No extra data
    inf.readEof();
    return 0;
}
