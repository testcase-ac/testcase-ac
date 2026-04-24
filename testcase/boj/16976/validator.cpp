#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, Q
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(2, N, "M");  // 2 ≤ M ≤ N
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");  // 1 ≤ Q ≤ 100000
    inf.readEoln();

    // Read games bought by each of the N people
    vector<int> cnt(M+1, 0);
    vector<int> games = inf.readInts(N, 1, M, "game");
    inf.readEoln();
    for (int i = 0; i < N; i++) {
        cnt[games[i]]++;
    }
    // Each game must be bought by at least one person
    for (int g = 1; g <= M; g++) {
        ensuref(cnt[g] >= 1, "Game %d has no players", g);
    }

    // Read the Q cables
    for (int i = 0; i < Q; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        // Self‐loops and multiple edges are allowed by the statement
    }

    inf.readEof();
    return 0;
}
