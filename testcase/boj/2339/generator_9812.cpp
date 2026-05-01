#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern = rnd.next(0, 7);
    int N;
    vector<vector<int>> g;

    auto printGrid = [&](int N, const vector<vector<int>>& grid) {
        println(N);
        for (int i = 0; i < N; ++i) {
            println(grid[i]);
        }
    };

    auto makeRandomBoard = [&](int N, int J, int I) {
        vector<vector<int>> board(N, vector<int>(N, 0));
        int total = N * N;
        vector<int> pos(total);
        for (int i = 0; i < total; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());

        int idx = 0;
        for (int k = 0; k < J; ++k) {
            int p = pos[idx++];
            board[p / N][p % N] = 2;
        }
        for (int k = 0; k < I; ++k) {
            int p = pos[idx++];
            board[p / N][p % N] = 1;
        }
        return board;
    };

    if (pattern == 6) {
        // Sample 1 from statement
        N = 8;
        g = {
            {0, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 2, 1, 0, 0, 2, 0},
            {0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 2, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };
        printGrid(N, g);
        return 0;
    }

    if (pattern == 7) {
        // Sample 2 from statement
        N = 5;
        g = {
            {0, 0, 0, 0, 0},
            {0, 2, 2, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 2, 1, 2, 0},
            {2, 0, 0, 0, 0}
        };
        printGrid(N, g);
        return 0;
    }

    if (pattern == 0) {
        // Very small random boards, possibly 0 or 1 jewels
        N = rnd.next(1, 4);
        int maxCells = N * N;
        int maxJ = min(2, maxCells);
        int J = rnd.next(0, maxJ);
        int maxI = min(2, maxCells - J);
        int I = rnd.next(0, maxI);
        g = makeRandomBoard(N, J, I);
    } else if (pattern == 1) {
        // Single jewel, some impurities (including cases with none)
        N = rnd.next(1, 8);
        int maxCells = N * N;
        int J = (maxCells > 0 ? 1 : 0);
        int maxI = (maxCells > J ? min(5, maxCells - J) : 0);
        int I = (maxI > 0 ? rnd.next(0, maxI) : 0);
        g = makeRandomBoard(N, J, I);
    } else if (pattern == 2) {
        // Several jewels, few impurities
        N = rnd.next(3, 10);
        int maxCells = N * N;
        int maxJ = min(7, min(15, maxCells));
        int J = (maxJ >= 2 ? rnd.next(2, maxJ) : maxJ);
        int maxI = min(5, maxCells - J);
        int I = (maxI > 0 ? rnd.next(0, maxI) : 0);
        g = makeRandomBoard(N, J, I);
    } else if (pattern == 3) {
        // Several jewels, many impurities
        N = rnd.next(3, 10);
        int maxCells = N * N;
        int maxJ = min(7, min(15, maxCells));
        int J = (maxJ >= 2 ? rnd.next(2, maxJ) : maxJ);
        int maxI = min(maxCells - J, J + 10);
        int I = (maxI > 0 ? rnd.next(1, maxI) : 0);
        g = makeRandomBoard(N, J, I);
    } else if (pattern == 4) {
        // Clustered region with jewels and impurities
        N = rnd.next(4, 10);
        g.assign(N, vector<int>(N, 0));
        int h = rnd.next(2, min(5, N));
        int w = rnd.next(2, min(5, N));
        int r1 = rnd.next(0, N - h);
        int c1 = rnd.next(0, N - w);
        int totalSub = h * w;

        int J = rnd.next(1, min(5, min(15, totalSub - 1)));
        int maxI = min(totalSub - J, J + 5);
        int I = rnd.next(1, maxI);

        vector<int> pos;
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                pos.push_back(i * w + j);
        shuffle(pos.begin(), pos.end());

        int idx = 0;
        for (int k = 0; k < J; ++k) {
            int p = pos[idx++];
            int rr = p / w;
            int cc = p % w;
            g[r1 + rr][c1 + cc] = 2;
        }
        for (int k = 0; k < I; ++k) {
            int p = pos[idx++];
            int rr = p / w;
            int cc = p % w;
            g[r1 + rr][c1 + cc] = 1;
        }
    } else if (pattern == 5) {
        // Line of jewels and perpendicular line of impurities
        N = rnd.next(4, 10);
        g.assign(N, vector<int>(N, 0));

        bool horizontalJewels = rnd.next(0, 1) == 0;
        int Jline = rnd.next(2, min(5, N));
        int Iline = rnd.next(1, min(5, N));

        int jewelRow = rnd.next(0, N - 1);
        int jewelCol = rnd.next(0, N - 1);

        if (horizontalJewels) {
            // Jewels in one row
            vector<int> cols(N);
            for (int j = 0; j < N; ++j) cols[j] = j;
            shuffle(cols.begin(), cols.end());
            for (int k = 0; k < Jline; ++k) {
                g[jewelRow][cols[k]] = 2;
            }

            // Impurities along a column
            int impCol = rnd.next(0, N - 1);
            vector<int> rows;
            for (int i = 0; i < N; ++i) if (i != jewelRow) rows.push_back(i);
            shuffle(rows.begin(), rows.end());
            for (int k = 0; k < Iline && k < (int)rows.size(); ++k) {
                int r = rows[k];
                g[r][impCol] = 1;
            }
        } else {
            // Jewels in one column
            vector<int> rows(N);
            for (int i = 0; i < N; ++i) rows[i] = i;
            shuffle(rows.begin(), rows.end());
            for (int k = 0; k < Jline; ++k) {
                g[rows[k]][jewelCol] = 2;
            }

            // Impurities along a row
            int impRow = rnd.next(0, N - 1);
            vector<int> cols;
            for (int j = 0; j < N; ++j) if (j != jewelCol) cols.push_back(j);
            shuffle(cols.begin(), cols.end());
            for (int k = 0; k < Iline && k < (int)cols.size(); ++k) {
                int c = cols[k];
                g[impRow][c] = 1;
            }
        }

        // A few random extra jewels (still <= 15 total)
        int currentJ = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (g[i][j] == 2) ++currentJ;

        int extraJmax = min(2, 15 - currentJ);
        int extraJ = (extraJmax > 0 ? rnd.next(0, extraJmax) : 0);

        vector<pair<int,int>> emptyCells;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (g[i][j] == 0)
                    emptyCells.push_back({i, j});
        shuffle(emptyCells.begin(), emptyCells.end());
        for (int k = 0; k < extraJ && k < (int)emptyCells.size(); ++k) {
            int r = emptyCells[k].first;
            int c = emptyCells[k].second;
            g[r][c] = 2;
        }
    }

    printGrid(N, g);
    return 0;
}
