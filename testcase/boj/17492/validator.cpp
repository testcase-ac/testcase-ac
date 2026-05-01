#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

int N;
int boardInit[10][10];
int dirs[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1,-1}, {-1,1}, {1,-1}, {1,1}
};

bool inside(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < N;
}

// Encode board state as bitmask of stones (only cells that can contain stones are non-wall cells)
struct StateEncoder {
    int idx[10][10];
    vector<pair<int,int>> pos; // index -> (r,c)
    int K; // number of possible stone positions

    StateEncoder() {
        K = 0;
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                idx[i][j] = -1;
    }

    void init() {
        K = 0;
        pos.clear();
        for (int r = 0; r < N; ++r)
            for (int c = 0; c < N; ++c)
                if (boardInit[r][c] != 1) { // not wall => could be stone or empty
                    idx[r][c] = K++;
                    pos.push_back({r,c});
                }
    }

    int encode(const int b[10][10]) const {
        int mask = 0;
        for (int k = 0; k < K; ++k) {
            int r = pos[k].first;
            int c = pos[k].second;
            if (b[r][c] == 2) {
                mask |= (1 << k);
            }
        }
        return mask;
    }

    int countBits(int mask) const {
        return __builtin_popcount((unsigned)mask);
    }
};

StateEncoder enc;

bool canWinFromStateMask(int startMask) {
    // BFS/DFS over state space; verify at least one sequence leads to exactly one stone.
    // Also used to check that stated promise "answer always exists or not bounded" doesn't contradict samples,
    // but mainly to ensure no hidden constraints; here we only use it to validate text promises:
    // The problem does NOT guarantee solvability, only asks to determine it,
    // so there is no global promise to verify. However, we can still run search
    // to check bounds like subtask constraints: #stones <= 7.
    // We'll use search later just to ensure stone count respects subtask bounds.

    // For potential extra checks, but not required by problem statement for validator correctness.
    // So we keep it simple and fast.

    // A trivial search to detect any reachable state with exactly one stone.
    // State space size: at most 2^K, K <= N*N <= 100, but stone count <= 7 so practical states << 2^100.

    set<int> vis;
    queue<int> q;
    vis.insert(startMask);
    q.push(startMask);

    while (!q.empty()) {
        int mask = q.front(); q.pop();
        int stones = enc.countBits(mask);
        if (stones == 1) return true;

        // Reconstruct board for move generation
        int b[10][10];
        for (int r = 0; r < N; ++r)
            for (int c = 0; c < N; ++c)
                b[r][c] = boardInit[r][c];
        for (int k = 0; k < enc.K; ++k) {
            if (mask & (1 << k)) {
                auto [r,c] = enc.pos[k];
                b[r][c] = 2;
            } else {
                auto [r,c] = enc.pos[k];
                if (b[r][c] != 1) b[r][c] = 0;
            }
        }

        // Generate moves
        for (int k = 0; k < enc.K; ++k) {
            if (!(mask & (1 << k))) continue;
            int r = enc.pos[k].first;
            int c = enc.pos[k].second;
            if (b[r][c] != 2) continue;
            for (int d = 0; d < 8; ++d) {
                int r1 = r + dirs[d][0];
                int c1 = c + dirs[d][1];
                int r2 = r + 2*dirs[d][0];
                int c2 = c + 2*dirs[d][1];
                if (!inside(r2, c2)) continue;
                if (b[r1][c1] != 2) continue;     // must jump over a stone
                if (b[r2][c2] != 0) continue;     // landing cell must be empty

                int overIdx = enc.idx[r1][c1];
                int toIdx   = enc.idx[r2][c2];
                // overIdx and toIdx must be valid because they are non-wall
                ensuref(overIdx != -1 && toIdx != -1,
                        "Internal encoder error: non-wall cell without index (%d,%d) or (%d,%d)",
                        r1, c1, r2, c2);

                int nmask = mask;
                nmask &= ~(1 << k);        // move from (r,c)
                nmask &= ~(1 << overIdx);  // remove jumped stone
                nmask |=  (1 << toIdx);    // place at landing cell

                if (!vis.count(nmask)) {
                    vis.insert(nmask);
                    q.push(nmask);
                }
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    N = inf.readInt(3, 10, "N");
    inf.readEoln();

    int stoneCount = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int v = inf.readInt(0, 2, "cell");
            boardInit[i][j] = v;
            if (j + 1 < N) inf.readSpace();
            else inf.readEoln();
            if (v == 2) stoneCount++;
        }
    }

    // Border cells are all walls (1)
    for (int i = 0; i < N; ++i) {
        ensuref(boardInit[0][i] == 1, "Top border cell (0,%d) must be wall (1)", i);
        ensuref(boardInit[N-1][i] == 1, "Bottom border cell (%d,%d) must be wall (1)", N-1, i);
        ensuref(boardInit[i][0] == 1, "Left border cell (%d,0) must be wall (1)", i);
        ensuref(boardInit[i][N-1] == 1, "Right border cell (%d,%d) must be wall (1)", i, N-1);
    }

    // Stones must be on non-wall cells; already implied by encoding, but we can check explicitly:
    // The text says "모든 바둑알은 빈 칸에 위치한다." = stones only on empty cells initially.
    // However, initial board uses value 2 for stones, not 0, so "빈 칸" here means
    // "cells that are not walls"; there is no separate 'empty' marker needed for initial check.
    // Thus, there is no extra condition: 2 is allowed only where !=1 (trivially true).
    // Still, we ensure there is at least one stone because subtasks say stone count >=1.
    ensuref(stoneCount >= 1, "There must be at least one stone (value 2), found %d", stoneCount);

    // Subtask global constraints:
    // Subtask 1: #stones in [1,2]; Subtask 2: #stones in [1,7].
    // The full problem merges them; the strongest global bound is #stones <= 7.
    ensuref(stoneCount <= 7,
            "Number of stones must be at most 7 (given %d), based on problem subtasks", stoneCount);

    // Initialize encoder and verify internal consistency
    enc.init();

    // Consistency: all cells with value 2 or 0 are non-walls (already true by construction),
    // but ensure encoder indexed all non-wall cells:
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (boardInit[r][c] != 1) {
                ensuref(enc.idx[r][c] != -1, "Non-wall cell (%d,%d) must have an index", r, c);
            }

    // As per instructions, if problem states some global promise like "answer always exists"
    // we must verify it. Here, the statement does NOT assert solvability for all inputs.
    // So we do NOT enforce any solvability condition.
    //
    // However, we already enforced the only extra global assumption:
    // - stone count between 1 and 7 inclusive (from subtasks).

    // Also check that simulation of moves never tries to jump over walls:
    // This is implicitly guaranteed by the rules and our search, but we can do a light self-check
    // by doing a dry run from initial state (no requirement to succeed).
    int startMask = enc.encode(boardInit);
    // During BFS, an ensuref will fire if any invalid move encoding occurs.
    // We don't care about the return value.
    (void)canWinFromStateMask(startMask);

    inf.readEof();
}
