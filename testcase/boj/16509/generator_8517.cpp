#include "testlib.h"
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int H = 10;
const int W = 9;

struct Move {
    int dr, dc;
    int br1r, br1c;
    int br2r, br2c;
};

bool inBounds(int r, int c) {
    return 0 <= r && r < H && 0 <= c && c < W;
}

// BFS from king position to compute distance to all cells
void bfs(int kr, int kc, int dist[H][W]) {
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            dist[i][j] = -1;

    // Sang moves with their blocking intermediate squares
    static const Move moves[8] = {
        {-3, -2, -1,  0, -2, -1}, // up-left
        {-3,  2, -1,  0, -2,  1}, // up-right
        { 3, -2,  1,  0,  2, -1}, // down-left
        { 3,  2,  1,  0,  2,  1}, // down-right
        {-2, -3,  0, -1, -1, -2}, // left-up
        { 2, -3,  0, -1,  1, -2}, // left-down
        {-2,  3,  0,  1, -1,  2}, // right-up
        { 2,  3,  0,  1,  1,  2}  // right-down
    };

    queue<pair<int,int>> q;
    dist[kr][kc] = 0;
    q.push({kr, kc});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (const auto &m : moves) {
            int p1r = r + m.br1r;
            int p1c = c + m.br1c;
            int p2r = r + m.br2r;
            int p2c = c + m.br2c;
            int nr  = r + m.dr;
            int nc  = c + m.dc;

            if (!inBounds(p1r, p1c) || !inBounds(p2r, p2c) || !inBounds(nr, nc))
                continue;

            // Path cannot pass through the king's square (as an intermediate)
            if ((p1r == kr && p1c == kc) || (p2r == kr && p2c == kc))
                continue;

            if (dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // All possible king positions in the two palaces
    vector<pair<int,int>> palace;
    int palaceRows[] = {0, 1, 2, 7, 8, 9};
    int palaceCols[] = {3, 4, 5};
    for (int ri = 0; ri < 6; ++ri)
        for (int ci = 0; ci < 3; ++ci)
            palace.push_back({palaceRows[ri], palaceCols[ci]});

    pair<int,int> sang, king;

    // Sometimes output one of the sample tests exactly (easier to verify)
    if (rnd.next(0, 4) == 0) { // 20% chance
        int which = rnd.next(0, 2);
        if (which == 0) {
            sang = {4, 2};
            king = {2, 5};
        } else if (which == 1) {
            sang = {0, 1};
            king = {8, 4};
        } else {
            sang = {0, 2};
            king = {1, 4};
        }
        println(sang.first, sang.second);
        println(king.first, king.second);
        return 0;
    }

    // Modes for diversity:
    // 0: completely random valid positions
    // 1: distance exactly 1
    // 2: distance exactly 2
    // 3: distance >= 3 (finite)
    // 4: unreachable (-1)
    int mode = rnd.next(0, 4);

    bool found = false;
    for (int attempt = 0; attempt < 50 && !found; ++attempt) {
        king = rnd.any(palace);

        if (mode == 0) {
            // Any starting position different from king
            int sr, sc;
            do {
                sr = rnd.next(0, H - 1);
                sc = rnd.next(0, W - 1);
            } while (sr == king.first && sc == king.second);
            sang = {sr, sc};
            found = true;
        } else {
            int dist[H][W];
            bfs(king.first, king.second, dist);

            vector<pair<int,int>> cand;
            for (int r = 0; r < H; ++r) {
                for (int c = 0; c < W; ++c) {
                    if (r == king.first && c == king.second) continue;
                    int d = dist[r][c];
                    if (mode == 1) {
                        if (d == 1) cand.push_back({r, c});
                    } else if (mode == 2) {
                        if (d == 2) cand.push_back({r, c});
                    } else if (mode == 3) {
                        if (d >= 3 && d != -1) cand.push_back({r, c});
                    } else if (mode == 4) {
                        if (d == -1) cand.push_back({r, c});
                    }
                }
            }

            if (!cand.empty()) {
                sang = rnd.any(cand);
                found = true;
            }
        }
    }

    if (!found) {
        // Fallback: completely random valid positions
        king = rnd.any(palace);
        int sr, sc;
        do {
            sr = rnd.next(0, H - 1);
            sc = rnd.next(0, W - 1);
        } while (sr == king.first && sc == king.second);
        sang = {sr, sc};
    }

    println(sang.first, sang.second);
    println(king.first, king.second);

    return 0;
}
