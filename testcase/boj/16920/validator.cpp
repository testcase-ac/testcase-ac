#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, P
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int P = inf.readInt(1, 9, "P");
    inf.readEoln();

    // 2. Read S_1..S_P
    vector<long long> S(P+1); // 1-based
    for (int i = 1; i <= P; ++i) {
        S[i] = inf.readLong(1LL, 1000000000LL, "S_i");
        if (i < P) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read N lines of grid
    vector<string> grid(N);
    vector<int> castle_count(P+1, 0); // 1-based
    set<pair<int,int>> castle_positions; // to check no two castles on same cell
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readLine("[.#1-9]{"+to_string(M)+"}", "grid row");
        ensuref((int)grid[i].size() == M, "Row %d: Expected length %d, got %d", i+1, M, (int)grid[i].size());
        for (int j = 0; j < M; ++j) {
            char c = grid[i][j];
            if (c >= '1' && c <= '9') {
                int player = c - '0';
                ensuref(1 <= player && player <= P, "Cell (%d,%d): Castle for player %d, but P=%d", i+1, j+1, player, P);
                castle_count[player]++;
                ensuref(!castle_positions.count({i,j}), "Duplicate castle at cell (%d,%d)", i+1, j+1);
                castle_positions.insert({i,j});
            } else if (c == '.' || c == '#') {
                // ok
            } else {
                ensuref(false, "Cell (%d,%d): Invalid character '%c'", i+1, j+1, c);
            }
        }
    }

    // 4. Check that every player has at least one castle
    for (int i = 1; i <= P; ++i) {
        ensuref(castle_count[i] >= 1, "Player %d does not have any castle", i);
    }

    // 5. Check that there are no castles for non-existent players
    // Already checked above: only '1'..'P' are allowed as castle chars

    // 6. Check that no two castles are on the same cell
    // Already checked above by set

    // 7. Check that each row is exactly M characters
    // Already checked above

    // 8. Check that the file ends with EOF
    inf.readEof();
}
