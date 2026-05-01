#include "testlib.h"
using namespace std;

void outputGrid(const vector<string>& g) {
    int N = (int)g.size();
    int M = (int)g[0].size();
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(g[i]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);
    vector<string> grid;

    if (scenario == 0) {
        // Very small grids: no sticks possible (N,M <= 2)
        int N = rnd.next(1, 2);
        int M = rnd.next(1, 2);
        grid.assign(N, string(M, 'R'));
        string colors = "RGW";
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.any(colors);
        outputGrid(grid);

    } else if (scenario == 1) {
        // Single row or single column (line cases)
        bool horizontal = rnd.next(0, 1);
        int len = rnd.next(3, 15);
        if (horizontal) {
            int N = 1, M = len;
            grid.assign(N, string(M, 'R'));
            int type = rnd.next(0, 2);
            if (type == 0) {
                // Pure RGW repeating: many possible sticks
                for (int j = 0; j < M; j++) {
                    int r = j % 3;
                    if (r == 0) grid[0][j] = 'R';
                    else if (r == 1) grid[0][j] = 'G';
                    else grid[0][j] = 'W';
                }
            } else {
                // Random colors on the line
                string colors = "RGW";
                for (int j = 0; j < M; j++)
                    grid[0][j] = rnd.any(colors);
            }
        } else {
            int N = len, M = 1;
            grid.assign(N, string(M, 'R'));
            int type = rnd.next(0, 2);
            if (type == 0) {
                // Pure vertical RGW repeating
                for (int i = 0; i < N; i++) {
                    int r = i % 3;
                    if (r == 0) grid[i][0] = 'R';
                    else if (r == 1) grid[i][0] = 'G';
                    else grid[i][0] = 'W';
                }
            } else {
                // Random colors on the line
                string colors = "RGW";
                for (int i = 0; i < N; i++)
                    grid[i][0] = rnd.any(colors);
            }
        }
        outputGrid(grid);

    } else if (scenario == 2) {
        // Small/medium random grid with biased color distribution
        int N = rnd.next(3, 10);
        int M = rnd.next(3, 10);
        grid.assign(N, string(M, 'R'));

        // Choose a bias pattern for colors
        int biasType = rnd.next(0, 3);
        string bag;
        if (biasType == 0) {
            // Nearly uniform
            bag = "RGW";
        } else if (biasType == 1) {
            // Many R
            bag = "RRRRGW";
        } else if (biasType == 2) {
            // Many G
            bag = "GGGGRW";
        } else {
            // Many W
            bag = "WWWwRG"; // though not used, leave for completeness
        }

        // Correct the last possibility to keep letters valid
        if (biasType == 3) bag = "WWWWRG";

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.any(bag);
        outputGrid(grid);

    } else if (scenario == 3) {
        // Horizontal RGW stripe patterns
        int N = rnd.next(3, 10);
        int M = rnd.next(3, 15);
        grid.assign(N, string(M, 'R'));

        string base = "RGW";
        for (int i = 0; i < N; i++) {
            int rowType = rnd.next(0, 2);
            if (rowType == 0) {
                // Clean repeating RGW with random offset
                int off = rnd.next(0, 2);
                for (int j = 0; j < M; j++) {
                    grid[i][j] = base[(j + off) % 3];
                }
            } else {
                // Mostly RGW pattern with some random noise
                int off = rnd.next(0, 2);
                string colors = "RGW";
                for (int j = 0; j < M; j++) {
                    if (rnd.next(0, 9) == 0) {
                        grid[i][j] = rnd.any(colors);
                    } else {
                        grid[i][j] = base[(j + off) % 3];
                    }
                }
            }
        }
        outputGrid(grid);

    } else if (scenario == 4) {
        // Vertical RGW stripe patterns
        int N = rnd.next(3, 15);
        int M = rnd.next(3, 10);
        grid.assign(N, string(M, 'R'));

        string base = "RGW";
        for (int j = 0; j < M; j++) {
            int colType = rnd.next(0, 2);
            if (colType == 0) {
                // Clean repeating RGW with random offset
                int off = rnd.next(0, 2);
                for (int i = 0; i < N; i++) {
                    grid[i][j] = base[(i + off) % 3];
                }
            } else {
                // Mostly RGW pattern with some random noise
                int off = rnd.next(0, 2);
                string colors = "RGW";
                for (int i = 0; i < N; i++) {
                    if (rnd.next(0, 9) == 0) {
                        grid[i][j] = rnd.any(colors);
                    } else {
                        grid[i][j] = base[(i + off) % 3];
                    }
                }
            }
        }
        outputGrid(grid);

    } else if (scenario == 5) {
        // Cross-lattice pattern creating many intersecting horizontal and vertical triples
        int N = rnd.next(5, 15);
        int M = rnd.next(5, 15);
        grid.assign(N, string(M, 'G'));

        // Base fill with random colors to add variety
        string colors = "RGW";
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.any(colors);

        // Overlay RGW crosses where possible
        for (int i = 1; i + 1 < N; i += 2) {
            for (int j = 1; j + 1 < M; j += 2) {
                grid[i][j] = 'G';        // center
                grid[i][j - 1] = 'R';    // left
                grid[i][j + 1] = 'W';    // right
                grid[i - 1][j] = 'R';    // top
                grid[i + 1][j] = 'W';    // bottom
            }
        }

        // Optional small random noise to break perfect regularity
        int noiseCells = rnd.next(0, N * M / 10);
        for (int k = 0; k < noiseCells; k++) {
            int i = rnd.next(0, N - 1);
            int j = rnd.next(0, M - 1);
            grid[i][j] = rnd.any(colors);
        }

        outputGrid(grid);
    }

    return 0;
}
