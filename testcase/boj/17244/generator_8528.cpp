#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M;
    vector<string> grid;

    // Choose scenario: bias towards more complex ones
    int scenario = rnd.wnext(3, 1) + 1; // 1..3, biased to 3

    if (scenario == 1) {
        // Scenario 1: Narrow corridor (mostly 1D path)
        bool vertical = rnd.next(0, 1);
        if (vertical) {
            N = rnd.next(3, 4);
            M = rnd.next(4, 12);
            grid.assign(M, string(N, '#'));
            int c = 1; // corridor column
            for (int r = 1; r <= M - 2; ++r) {
                grid[r][c] = '.';
            }
        } else {
            M = rnd.next(3, 4);
            N = rnd.next(4, 12);
            grid.assign(M, string(N, '#'));
            int r = 1; // corridor row
            for (int c = 1; c <= N - 2; ++c) {
                grid[r][c] = '.';
            }
        }
    } else if (scenario == 2) {
        // Scenario 2: Open box (many open cells)
        N = rnd.next(4, 10);
        M = rnd.next(4, 10);
        grid.assign(M, string(N, '#'));
        for (int r = 1; r <= M - 2; ++r) {
            for (int c = 1; c <= N - 2; ++c) {
                grid[r][c] = '.';
            }
        }
    } else {
        // Scenario 3: Labyrinth-like region using DFS carving
        N = rnd.next(5, 15);
        M = rnd.next(5, 15);
        grid.assign(M, string(N, '#'));

        int sr = rnd.next(1, M - 2);
        int sc = rnd.next(1, N - 2);
        grid[sr][sc] = '.';

        vector<pair<int,int>> cells;
        cells.push_back({sr, sc});

        vector<pair<int,int>> stack;
        stack.push_back({sr, sc});

        int carveProb = rnd.any(vector<int>{30, 50, 70, 85}); // percentage
        int minCells = 2;

        static int dr[4] = {-1, 1, 0, 0};
        static int dc[4] = {0, 0, -1, 1};

        while (!stack.empty()) {
            auto cur = stack.back();
            stack.pop_back();
            int r = cur.first;
            int c = cur.second;

            vector<int> dirs = {0, 1, 2, 3};
            shuffle(dirs.begin(), dirs.end());

            for (int k : dirs) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr <= 0 || nr >= M - 1 || nc <= 0 || nc >= N - 1) continue;
                if (grid[nr][nc] == '#') {
                    bool force = ((int)cells.size() < minCells);
                    if (force || rnd.next(100) < carveProb) {
                        grid[nr][nc] = '.';
                        cells.push_back({nr, nc});
                        stack.push_back({nr, nc});
                    }
                }
            }
        }

        // Safety fallback: if something went wrong, make interior open
        int openCnt = 0;
        for (int r = 1; r <= M - 2; ++r)
            for (int c = 1; c <= N - 2; ++c)
                if (grid[r][c] == '.') ++openCnt;
        if (openCnt < 2) {
            for (int r = 1; r <= M - 2; ++r)
                for (int c = 1; c <= N - 2; ++c)
                    grid[r][c] = '.';
        }
    }

    // Collect interior open cells ('.') to work with
    vector<pair<int,int>> cells;
    for (int r = 1; r <= M - 2; ++r) {
        for (int c = 1; c <= N - 2; ++c) {
            if (grid[r][c] == '.') {
                cells.push_back({r, c});
            }
        }
    }

    // Ensure at least one open cell exists
    if (cells.empty()) {
        int r = M / 2;
        int c = N / 2;
        if (r <= 0) r = 1;
        if (r >= M - 1) r = M - 2;
        if (c <= 0) c = 1;
        if (c >= N - 1) c = N - 2;
        grid[r][c] = '.';
        cells.push_back({r, c});
    }

    // Choose a base open cell from which we'll guarantee connection to exit
    pair<int,int> base = rnd.any(cells);

    // Choose border position for exit E
    int er, ec;
    int side = rnd.next(0, 3); // 0: top, 1: bottom, 2: left, 3: right
    if (side == 0) {
        er = 0;
        ec = rnd.next(1, N - 2);
    } else if (side == 1) {
        er = M - 1;
        ec = rnd.next(1, N - 2);
    } else if (side == 2) {
        ec = 0;
        er = rnd.next(1, M - 2);
    } else {
        ec = N - 1;
        er = rnd.next(1, M - 2);
    }

    // Interior neighbor of the exit (guaranteed inside the grid)
    int nr, nc;
    if (er == 0) {
        nr = 1; nc = ec;
    } else if (er == M - 1) {
        nr = M - 2; nc = ec;
    } else if (ec == 0) {
        nr = er; nc = 1;
    } else { // ec == N-1
        nr = er; nc = N - 2;
    }

    // Carve a Manhattan path from base to (nr, nc) inside the house
    {
        int r = base.first;
        int c = base.second;
        while (r != nr) {
            r += (nr > r) ? 1 : -1;
            if (r > 0 && r < M - 1 && c > 0 && c < N - 1)
                grid[r][c] = '.';
        }
        while (c != nc) {
            c += (nc > c) ? 1 : -1;
            if (r > 0 && r < M - 1 && c > 0 && c < N - 1)
                grid[r][c] = '.';
        }
    }

    // Rebuild list of interior open cells after path carving
    cells.clear();
    for (int r = 1; r <= M - 2; ++r) {
        for (int c = 1; c <= N - 2; ++c) {
            if (grid[r][c] == '.') {
                cells.push_back({r, c});
            }
        }
    }

    // Choose S and item locations among interior open cells
    shuffle(cells.begin(), cells.end());

    // Place S
    pair<int,int> spos = cells[0];

    int maxItems = 0;
    if ((int)cells.size() > 1)
        maxItems = min(5, (int)cells.size() - 1);

    int numItems = 0;
    if (maxItems > 0) {
        if (scenario == 1) {
            // Corridor: often few items
            numItems = rnd.wnext(maxItems + 1, -2); // skew towards fewer
        } else if (scenario == 2) {
            // Open box: uniform
            numItems = rnd.next(0, maxItems);
        } else {
            // Labyrinth: if many cells, bias towards more items
            if ((int)cells.size() >= 10)
                numItems = rnd.wnext(maxItems + 1, 2); // skew towards more
            else
                numItems = rnd.next(0, maxItems);
        }
    }

    // Mark S
    grid[spos.first][spos.second] = 'S';

    // Mark items X (avoid overwriting S)
    for (int i = 1; i <= numItems; ++i) {
        auto p = cells[i];
        if (p == spos) continue;
        grid[p.first][p.second] = 'X';
    }

    // Place exit E on the border
    grid[er][ec] = 'E';

    // Output
    println(N, M);
    for (int r = 0; r < M; ++r)
        println(grid[r]);

    return 0;
}
