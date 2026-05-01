#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K;

    // Choose general size profile
    int sizeType = rnd.next(0, 3);
    if (sizeType == 0) {
        // Very small
        N = rnd.next(1, 3);
        K = rnd.next(1, 10);
    } else if (sizeType == 1) {
        // Small
        N = rnd.next(3, 7);
        K = rnd.next(5, 20);
    } else {
        // Medium
        N = rnd.next(7, 12);
        K = rnd.next(10, 35);
    }

    // Occasionally force 1x1 grid as a corner case
    if (rnd.next(0, 9) == 0) {
        N = 1;
        K = rnd.next(1, 10);
    }

    // Decide ink string length I
    int I;
    if (rnd.next(0, 4) == 0) {
        // Many tests with single ink color
        I = 1;
    } else {
        I = rnd.next(2, 7); // keep small but varied
    }

    // Build ink string
    string ink;
    if (I == 1) {
        string palette = "RGBYUABC";
        ink = string(1, rnd.any(palette));
    } else {
        // Sometimes use nice patterns from statement
        if (I == 3 && rnd.next(0, 1) == 0) {
            ink = "RGB";
        } else if (I == 7 && rnd.next(0, 1) == 0) {
            ink = "UTILCUP";
        } else if (I == 4 && rnd.next(0, 1) == 0) {
            ink = "ABCD";
        } else {
            string palette = "RGBYMCOP"; // a few distinct colors
            ink.resize(I);
            for (int i = 0; i < I; i++) {
                ink[i] = rnd.any(palette);
            }
        }
    }

    // Build grid
    vector<string> grid(N, string(N, '.'));

    if (N == 1) {
        // Only the player
        grid[0][0] = '@';
    } else {
        // Place random obstacles
        int obstaclePercent;
        if (N <= 3) obstaclePercent = rnd.next(10, 40);
        else obstaclePercent = rnd.next(20, 70);

        int obstacleCount = 0, emptyCount = 0;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                if (rnd.next(0, 99) < obstaclePercent) {
                    grid[y][x] = '#';
                    obstacleCount++;
                } else {
                    grid[y][x] = '.';
                    emptyCount++;
                }
            }
        }

        // Ensure at least one empty cell for the player
        if (emptyCount == 0) {
            int ry = rnd.next(0, N - 1);
            int rx = rnd.next(0, N - 1);
            grid[ry][rx] = '.';
            obstacleCount--;
            emptyCount++;
        }

        // Choose starting position on an empty cell
        vector<pair<int,int>> empties;
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                if (grid[y][x] == '.')
                    empties.push_back({y, x});

        pair<int,int> start = rnd.any(empties);
        int sy = start.first;
        int sx = start.second;
        grid[sy][sx] = '@';

        // Ensure there is at least one obstacle near the start (Manhattan dist <= 2)
        bool hasNearObstacle = false;
        vector<pair<int,int>> nearCells;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                if (y == sy && x == sx) continue;
                if (abs(y - sy) + abs(x - sx) <= 2) {
                    nearCells.push_back({y, x});
                    if (grid[y][x] == '#') hasNearObstacle = true;
                }
            }
        }
        if (!hasNearObstacle && !nearCells.empty()) {
            pair<int,int> p = rnd.any(nearCells);
            if (grid[p.first][p.second] != '@')
                grid[p.first][p.second] = '#';
        }
    }

    // Build commands string of length K
    string moves = "UDLR";
    string cmds(K, 'U'); // temporary init

    int cmdStyle = rnd.next(0, 2);
    if (cmdStyle == 0) {
        // Per-command random with some bias
        for (int i = 0; i < K; i++) {
            double r = rnd.next();
            if (r < 0.35) {
                cmds[i] = 'j';
            } else if (r < 0.60) {
                cmds[i] = 'J';
            } else {
                cmds[i] = rnd.any(moves);
            }
        }
    } else {
        // Compose from small patterns
        string built;
        while ((int)built.size() < K) {
            int segType = rnd.next(0, 2);
            if (segType == 0) {
                // A run of moves
                int len = rnd.next(1, 4);
                for (int i = 0; i < len; i++)
                    built += rnd.any(moves);
            } else if (segType == 1) {
                // A run of charge commands
                int len = rnd.next(1, 4);
                built.append(len, 'j');
            } else {
                // Mixed jump patterns
                vector<string> pats = {"J", "jJ", "jjJ", "Jjj", "JJ", "jjjjJ"};
                built += rnd.any(pats);
            }
        }
        cmds = built.substr(0, K);
    }

    // Ensure presence of at least one 'J' and (if possible) one 'j'
    if (K == 1) {
        // Prefer to have at least one jump
        if (cmds[0] != 'J') cmds[0] = 'J';
    } else {
        bool hasJ = false, hasj = false;
        for (char c : cmds) {
            if (c == 'J') hasJ = true;
            if (c == 'j') hasj = true;
        }
        if (!hasJ) cmds[0] = 'J';
        if (!hasj) cmds[1] = 'j';
    }

    // Output
    println(I, N, K);
    println(ink);
    for (int y = 0; y < N; y++) {
        println(grid[y]);
    }
    println(cmds);

    return 0;
}
