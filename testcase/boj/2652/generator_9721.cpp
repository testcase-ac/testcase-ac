#include "testlib.h"
using namespace std;

struct Cell {
    int r, c;
};

vector<Cell> genDShapeLocal(int H, int W) {
    // side: 0=top,1=bottom,2=left,3=right
    int side = rnd.next(0, 3);
    int ih = rnd.next(1, H - 2);
    int iw = rnd.next(1, W - 2);
    int ix, iy;

    if (side == 0) { // top indentation
        iy = 0;
        ix = rnd.next(1, W - iw - 1);
    } else if (side == 1) { // bottom indentation
        iy = H - ih;
        ix = rnd.next(1, W - iw - 1);
    } else if (side == 2) { // left indentation
        ix = 0;
        iy = rnd.next(1, H - ih - 1);
    } else { // right indentation
        ix = W - iw;
        iy = rnd.next(1, H - ih - 1);
    }

    vector<Cell> cells;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            bool inInner = (i >= iy && i < iy + ih && j >= ix && j < ix + iw);
            if (!inInner) cells.push_back({i, j});
        }
    }
    return cells;
}

bool placeDShape(vector<vector<int>>& board, int H, int W) {
    int N = (int)board.size();
    if (H > N || W > N) return false;

    vector<Cell> local = genDShapeLocal(H, W);

    for (int attempt = 0; attempt < 30; ++attempt) {
        int r0 = rnd.next(0, N - H);
        int c0 = rnd.next(0, N - W);

        bool ok = true;
        for (const auto& cell : local) {
            int r = r0 + cell.r;
            int c = c0 + cell.c;
            if (board[r][c] == 1) {
                ok = false;
                break;
            }
            static const int dr[4] = {-1, 1, 0, 0};
            static const int dc[4] = {0, 0, -1, 1};
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (0 <= nr && nr < N && 0 <= nc && nc < N) {
                    if (board[nr][nc] == 1) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) break;
        }

        if (!ok) continue;

        for (const auto& cell : local) {
            int r = r0 + cell.r;
            int c = c0 + cell.c;
            board[r][c] = 1;
        }
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Board size: keep small for readability, but varied
    int mode = rnd.next(0, 4);
    int N;
    if (mode == 0) N = rnd.next(3, 6);
    else if (mode == 1) N = rnd.next(6, 9);
    else if (mode == 2) N = rnd.next(8, 12);
    else N = rnd.next(10, 15);

    // Generate parameters u, v, w, x, y (all positive)
    int u, v, w, x, y;
    if (rnd.next(0, 4) == 0 && N >= 5) {
        // Sometimes use a fixed pattern similar to the sample
        u = 5; v = 1; w = 1; x = 1; y = 3;
    } else {
        // Random but moderate sizes, all <= N
        u = rnd.next(1, N);
        v = rnd.next(1, N);
        w = rnd.next(1, N);
        x = rnd.next(1, N);
        y = rnd.next(1, N);
    }

    vector<vector<int>> board(N, vector<int>(N, 0));

    // Decide how many D-shaped blocks to try placing
    int maxK = min(4, max(1, N / 3));
    int targetK = rnd.next(0, maxK);

    int placed = 0;
    int attempts = 0;
    int maxAttempts = 60;

    while (placed < targetK && attempts < maxAttempts) {
        ++attempts;
        // Prefer medium-to-large blocks but keep within board
        int H = 3 + rnd.wnext(max(1, N - 2), 2); // in [3, N]
        int W = 3 + rnd.wnext(max(1, N - 2), 2); // in [3, N]
        if (H > N) H = N;
        if (W > N) W = N;
        if (H < 3) H = 3;
        if (W < 3) W = 3;

        if (placeDShape(board, H, W)) {
            ++placed;
        }
    }

    println(N);
    println(u, v, w, x, y);
    for (int i = 0; i < N; ++i) {
        println(board[i]);
    }

    return 0;
}
