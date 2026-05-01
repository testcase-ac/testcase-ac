#include "testlib.h"
using namespace std;

struct Cell {
    int r, c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> board;

    int mode = rnd.next(0, 2); // 0: preset examples, 1: corridor, 2: random board

    if (mode == 0) {
        // Preset boards from problem examples (some solvable, some not)
        vector< vector<string> > presets;

        // Example 1
        presets.push_back({
            "#####",
            "#..B#",
            "#.#.#",
            "#RO.#",
            "#####"
        });

        // Example 2
        presets.push_back({
            "#######",
            "#...RB#",
            "#.#####",
            "#.....#",
            "#####.#",
            "#O....#",
            "#######"
        });

        // Example 3
        presets.push_back({
            "#######",
            "#..R#B#",
            "#.#####",
            "#.....#",
            "#####.#",
            "#O....#",
            "#######"
        });

        // Example 4 (unsolvable)
        presets.push_back({
            "##########",
            "#R#...##B#",
            "#...#.##.#",
            "#####.##.#",
            "#......#.#",
            "#.######.#",
            "#.#....#.#",
            "#.#.#.#..#",
            "#...#.O#.#",
            "##########"
        });

        // Example 5
        presets.push_back({
            "#######",
            "#R.O.B#",
            "#######"
        });

        // Example 6
        presets.push_back({
            "##########",
            "#R#...##B#",
            "#...#.##.#",
            "#####.##.#",
            "#......#.#",
            "#.######.#",
            "#.#....#.#",
            "#.#.##...#",
            "#O..#....#",
            "##########"
        });

        // Example 7 (unsolvable)
        presets.push_back({
            "##########",
            "#.O....RB#",
            "##########"
        });

        board = rnd.any(presets);
    } else if (mode == 1) {
        // Corridor-style boards (very small and easy to reason about)
        bool horizontal = rnd.next(0, 1) == 1;

        if (horizontal) {
            // 3 x M, single corridor row in the middle
            int N = 3;
            int M = rnd.next(5, 10);
            board.assign(N, string(M, '#'));
            for (int j = 1; j <= M - 2; ++j)
                board[1][j] = '.';

            // Place O, R, B on distinct columns in the middle row
            vector<int> cols;
            for (int j = 1; j <= M - 2; ++j)
                cols.push_back(j);
            shuffle(cols.begin(), cols.end());

            int jO = cols[0];
            int jR = cols[1];
            int jB = cols[2];

            board[1][jO] = 'O';
            board[1][jR] = 'R';
            board[1][jB] = 'B';

            // Optional extra walls in the corridor (not on R/B/O)
            int freeSlots = (M - 2) - 3; // minus R, B, O
            if (freeSlots < 0) freeSlots = 0;
            int extraWalls = (freeSlots > 0 ? rnd.next(0, freeSlots) : 0);

            vector<int> empties;
            for (int j = 1; j <= M - 2; ++j)
                if (board[1][j] == '.')
                    empties.push_back(j);
            shuffle(empties.begin(), empties.end());
            for (int k = 0; k < extraWalls && k < (int)empties.size(); ++k)
                board[1][empties[k]] = '#';
        } else {
            // N x 3, single corridor column in the middle
            int N = rnd.next(5, 10);
            int M = 3;
            board.assign(N, string(M, '#'));
            for (int i = 1; i <= N - 2; ++i)
                board[i][1] = '.';

            // Place O, R, B on distinct rows in the middle column
            vector<int> rows;
            for (int i = 1; i <= N - 2; ++i)
                rows.push_back(i);
            shuffle(rows.begin(), rows.end());

            int iO = rows[0];
            int iR = rows[1];
            int iB = rows[2];

            board[iO][1] = 'O';
            board[iR][1] = 'R';
            board[iB][1] = 'B';

            // Optional extra walls in the corridor (not on R/B/O)
            int freeSlots = (N - 2) - 3; // minus R, B, O
            if (freeSlots < 0) freeSlots = 0;
            int extraWalls = (freeSlots > 0 ? rnd.next(0, freeSlots) : 0);

            vector<int> empties;
            for (int i = 1; i <= N - 2; ++i)
                if (board[i][1] == '.')
                    empties.push_back(i);
            shuffle(empties.begin(), empties.end());
            for (int k = 0; k < extraWalls && k < (int)empties.size(); ++k)
                board[empties[k]][1] = '#';
        }
    } else {
        // Random general boards with variable wall density
        int N, M;
        while (true) {
            N = rnd.next(3, 10);
            M = rnd.next(3, 10);
            if ((N - 2) * (M - 2) >= 3)
                break; // need at least 3 inner cells for O, R, B
        }

        board.assign(N, string(M, '#'));

        // Make all inner cells empty initially
        for (int i = 1; i <= N - 2; ++i)
            for (int j = 1; j <= M - 2; ++j)
                board[i][j] = '.';

        // Choose positions for O, R, B among inner cells
        vector<Cell> cells;
        for (int i = 1; i <= N - 2; ++i)
            for (int j = 1; j <= M - 2; ++j)
                cells.push_back({i, j});
        shuffle(cells.begin(), cells.end());

        Cell o = cells[0];
        Cell r = cells[1];
        Cell b = cells[2];

        board[o.r][o.c] = 'O';
        board[r.r][r.c] = 'R';
        board[b.r][b.c] = 'B';

        // Random walls in the inner area, skipping R/B/O
        int probWall = rnd.next(5, 40); // percentage chance of a wall on any empty inner cell
        for (int i = 1; i <= N - 2; ++i) {
            for (int j = 1; j <= M - 2; ++j) {
                if (board[i][j] == '.') {
                    if (rnd.next(100) < probWall)
                        board[i][j] = '#';
                }
            }
        }

        // Ensure the hole has at least one non-wall neighbor inside the board
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};
        int open = 0;
        for (int d = 0; d < 4; ++d) {
            int ni = o.r + dr[d];
            int nj = o.c + dc[d];
            if (ni < 1 || ni > N - 2 || nj < 1 || nj > M - 2) continue;
            if (board[ni][nj] != '#') open++;
        }
        if (open == 0) {
            vector<Cell> neigh;
            for (int d = 0; d < 4; ++d) {
                int ni = o.r + dr[d];
                int nj = o.c + dc[d];
                if (ni < 1 || ni > N - 2 || nj < 1 || nj > M - 2) continue;
                neigh.push_back({ni, nj});
            }
            if (!neigh.empty()) {
                Cell c = rnd.any(neigh);
                if (board[c.r][c.c] == '#')
                    board[c.r][c.c] = '.';
            }
        }
    }

    int N = (int)board.size();
    int M = (int)board[0].size();

    println(N, M);
    for (int i = 0; i < N; ++i)
        println(board[i]);

    return 0;
}
