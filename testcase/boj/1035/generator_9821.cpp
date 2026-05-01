#include "testlib.h"
using namespace std;

struct Cell {
    int r, c;
};

vector<Cell> buildConnected(int k, bool used[5][5]) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            used[i][j] = false;

    vector<Cell> cells;
    int sr = rnd.next(0, 4);
    int sc = rnd.next(0, 4);
    used[sr][sc] = true;
    cells.push_back({sr, sc});

    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};

    while ((int)cells.size() < k) {
        vector<Cell> cand;
        for (auto cur : cells) {
            for (int d = 0; d < 4; ++d) {
                int nr = cur.r + dr[d];
                int nc = cur.c + dc[d];
                if (0 <= nr && nr < 5 && 0 <= nc && nc < 5 && !used[nr][nc]) {
                    cand.push_back({nr, nc});
                }
            }
        }
        // there will always be at least one candidate for k <= 5
        Cell ch = cand[rnd.next(0, (int)cand.size() - 1)];
        if (!used[ch.r][ch.c]) {
            used[ch.r][ch.c] = true;
            cells.push_back(ch);
        }
    }
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> board(5, string(5, '.'));

    int scenario = rnd.next(1, 8);

    if (scenario == 1) {
        // Fixed sample 1
        board = {
            "*...*",
            ".....",
            ".....",
            ".....",
            "*...*"
        };
    } else if (scenario == 2) {
        // Fixed sample 2
        board = {
            ".....",
            "..**.",
            ".....",
            "...*.",
            "....."
        };
    } else if (scenario == 3) {
        // Fixed sample 3 (already connected)
        board = {
            ".....",
            ".....",
            ".**..",
            ".*...",
            "**..."
        };
    } else if (scenario == 4) {
        // Random connected cluster, size 1~5
        int k = rnd.next(1, 5);
        bool used[5][5];
        vector<Cell> cells = buildConnected(k, used);
        for (auto cur : cells) {
            board[cur.r][cur.c] = '*';
        }
    } else if (scenario == 5) {
        // Two pieces far apart
        int type = rnd.next(0, 2);
        if (type == 0) {
            board[0][0] = '*';
            board[4][4] = '*';
        } else if (type == 1) {
            board[0][4] = '*';
            board[4][0] = '*';
        } else {
            board[0][2] = '*';
            board[4][2] = '*';
        }
    } else if (scenario == 6) {
        // Four corners
        board[0][0] = '*';
        board[0][4] = '*';
        board[4][0] = '*';
        board[4][4] = '*';
    } else if (scenario == 7) {
        // Connected cluster + one isolated far piece
        int clusterSize = rnd.next(2, 4); // total pieces will be clusterSize + 1 (<=5)
        bool used[5][5];
        vector<Cell> cells = buildConnected(clusterSize, used);

        // Choose an isolated cell not adjacent to cluster
        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};
        while (true) {
            int pos = rnd.next(0, 24);
            int r = pos / 5;
            int c = pos % 5;
            if (used[r][c]) continue;
            bool adj = false;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (0 <= nr && nr < 5 && 0 <= nc && nc < 5 && used[nr][nc]) {
                    adj = true;
                    break;
                }
            }
            if (!adj) {
                used[r][c] = true;
                cells.push_back({r, c});
                break;
            }
        }
        for (auto cur : cells) {
            board[cur.r][cur.c] = '*';
        }
    } else if (scenario == 8) {
        // Completely random placement of 1~5 pieces
        int k = rnd.next(1, 5);
        vector<int> all(25);
        for (int i = 0; i < 25; ++i) all[i] = i;
        shuffle(all.begin(), all.end());
        for (int i = 0; i < k; ++i) {
            int pos = all[i];
            int r = pos / 5;
            int c = pos % 5;
            board[r][c] = '*';
        }
    }

    for (int i = 0; i < 5; ++i)
        println(board[i]);

    return 0;
}
