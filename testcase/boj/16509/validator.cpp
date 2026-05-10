#include "testlib.h"
#include <queue>
#include <vector>

using namespace std;

struct Pos {
    int r, c;
};

bool inBoard(int r, int c) {
    return 0 <= r && r <= 9 && 0 <= c && c <= 8;
}

// Check if (r, c) is inside one of the two palace rectangles
bool inPalace(int r, int c) {
    bool upper = (0 <= r && r <= 2 && 3 <= c && c <= 5);
    bool lower = (7 <= r && r <= 9 && 3 <= c && c <= 5);
    return upper || lower;
}

// For a given start and king position, compute minimal moves or -1 (for validator)
int bfsMinMoves(Pos start, Pos king) {
    static const int drFirst[4] = {-1, 1, 0, 0}; // up, down, left, right
    static const int dcFirst[4] = {0, 0, -1, 1};
    // For each primary direction, 2 diagonal possibilities:
    // After moving 1 step in primary direction, then 2 steps diagonally outward.
    // We'll explicitly code the 8 legs with their intermediate blocking squares.

    // 8 moves: (sequence of 3 steps; we need the 2 intermediate blocking cells)
    struct Move {
        int er, ec;     // end position delta
        int br1, bc1;   // first blocking cell delta from start
        int br2, bc2;   // second blocking cell delta from start
    };

    // These are hard-coded from known janggi elephant (sang) moves on grid.
    // Directions relative to (r, c):
    // Up-left:
    //   (r-1, c), then (r-2, c-1), (r-3, c-2) end at (r-3, c-2)
    // Up-right:
    //   (r-1, c), then (r-2, c+1), (r-3, c+2) end at (r-3, c+2)
    // Down-left:
    //   (r+1, c), then (r+2, c-1), (r+3, c-2) end at (r+3, c-2)
    // Down-right:
    //   (r+1, c), then (r+2, c+1), (r+3, c+2) end at (r+3, c+2)
    // Left-up:
    //   (r, c-1), then (r-1, c-2), (r-2, c-3) end at (r-2, c-3)
    // Left-down:
    //   (r, c-1), then (r+1, c-2), (r+2, c-3) end at (r+2, c-3)
    // Right-up:
    //   (r, c+1), then (r-1, c+2), (r-2, c+3) end at (r-2, c+3)
    // Right-down:
    //   (r, c+1), then (r+1, c+2), (r+2, c+3) end at (r+2, c+3)
    Move moves[8] = {
        {-3, -2, -1, 0, -2, -1}, // up-left
        {-3,  2, -1, 0, -2,  1}, // up-right
        { 3, -2,  1, 0,  2, -1}, // down-left
        { 3,  2,  1, 0,  2,  1}, // down-right
        {-2, -3,  0,-1, -1,-2}, // left-up
        { 2, -3,  0,-1,  1,-2}, // left-down
        {-2,  3,  0, 1, -1, 2}, // right-up
        { 2,  3,  0, 1,  1, 2}  // right-down
    };

    vector<vector<int>> dist(10, vector<int>(9, -1));
    queue<Pos> q;

    dist[start.r][start.c] = 0;
    q.push(start);

    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        if (cur.r == king.r && cur.c == king.c)
            return dist[cur.r][cur.c];

        for (int i = 0; i < 8; ++i) {
            int nr = cur.r + moves[i].er;
            int nc = cur.c + moves[i].ec;

            if (!inBoard(nr, nc)) continue;
            if (dist[nr][nc] != -1) continue;

            int br1r = cur.r + moves[i].br1;
            int br1c = cur.c + moves[i].bc1;
            int br2r = cur.r + moves[i].br2;
            int br2c = cur.c + moves[i].bc2;

            // All blocking cells must be on the board
            if (!inBoard(br1r, br1c) || !inBoard(br2r, br2c)) continue;

            // The only piece on the board is the king at its position.
            // Sang cannot move if king occupies any blocking cell on the path.
            if ((br1r == king.r && br1c == king.c) ||
                (br2r == king.r && br2c == king.c))
                continue;

            dist[nr][nc] = dist[cur.r][cur.c] + 1;
            q.push({nr, nc});
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test, strict whitespace:
    int R1 = inf.readInt(0, 9, "R1");
    inf.readSpace();
    int C1 = inf.readInt(0, 8, "C1");
    inf.readEoln();

    int R2 = inf.readInt(0, 9, "R2");
    inf.readSpace();
    int C2 = inf.readInt(0, 8, "C2");
    inf.readEoln();

    // Positions must be distinct
    ensuref(!(R1 == R2 && C1 == C2),
            "Sang and king positions must not coincide: (%d,%d)", R1, C1);

    // King must be in one of the two palaces
    ensuref(inPalace(R2, C2),
            "King must be inside one of the palaces, but is at (%d,%d)", R2, C2);

    // Optional holistic check: compute minimal moves to ensure it fits int range
    // (always true for such a small board, but we can still run BFS consistently)
    Pos sang{R1, C1}, king{R2, C2};
    int minMoves = bfsMinMoves(sang, king);
    // No specific bound given in statement besides being finite or -1,
    // but we can still sanity-check:
    ensuref(minMoves >= -1 && minMoves <= 1000,
            "Computed minimal moves out of reasonable range: %d", minMoves);

    inf.readEof();
}
