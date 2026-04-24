#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Pos { int z, x, y; };

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    for (int tc = 0; tc < T; tc++) {
        bool solvable = rnd.next() < 0.7;
        int L, R, C;
        // choose dimensions with at least 2 cells
        do {
            L = rnd.next(1, 5);
            R = rnd.next(1, 5);
            C = rnd.next(1, 5);
        } while (L * R * C < 2);
        // if too small to make unsolvable, force solvable
        if (!solvable && L * R * C < 3) solvable = true;

        // helper to pick a random position
        auto randPos = [&]() {
            return Pos{ rnd.next(0, L - 1),
                        rnd.next(0, R - 1),
                        rnd.next(0, C - 1) };
        };
        // check adjacency
        auto manh = [&](const Pos& a, const Pos& b) {
            return abs(a.z - b.z) + abs(a.x - b.x) + abs(a.y - b.y);
        };

        // pick S and E
        Pos S, E;
        do {
            S = randPos();
            E = randPos();
        } while ((S.z == E.z && S.x == E.x && S.y == E.y)
                 || (!solvable && manh(S, E) <= 1));

        // initialize all walls
        vector<vector<string>> grid(L, vector<string>(R, string(C, '#')));
        if (solvable) {
            // carve a monotonic path from S to E
            Pos cur = S;
            grid[cur.z][cur.x][cur.y] = '.';
            while (cur.z != E.z || cur.x != E.x || cur.y != E.y) {
                vector<Pos> moves;
                if (cur.z < E.z) moves.push_back(Pos{cur.z+1, cur.x, cur.y});
                if (cur.z > E.z) moves.push_back(Pos{cur.z-1, cur.x, cur.y});
                if (cur.x < E.x) moves.push_back(Pos{cur.z, cur.x+1, cur.y});
                if (cur.x > E.x) moves.push_back(Pos{cur.z, cur.x-1, cur.y});
                if (cur.y < E.y) moves.push_back(Pos{cur.z, cur.x, cur.y+1});
                if (cur.y > E.y) moves.push_back(Pos{cur.z, cur.x, cur.y-1});
                cur = rnd.any(moves);
                grid[cur.z][cur.x][cur.y] = '.';
            }
            // add some random extra empties
            vector<double> probs = {0.0, 0.1, 0.2, 0.3};
            double fill_prob = rnd.any(probs);
            for (int z = 0; z < L; z++) {
                for (int x = 0; x < R; x++) {
                    for (int y = 0; y < C; y++) {
                        if (grid[z][x][y] == '#' && rnd.next() < fill_prob) {
                            grid[z][x][y] = '.';
                        }
                    }
                }
            }
        }
        // place S and E
        grid[S.z][S.x][S.y] = 'S';
        grid[E.z][E.x][E.y] = 'E';

        // output this test case
        println(L, R, C);
        for (int z = 0; z < L; z++) {
            for (int x = 0; x < R; x++) {
                println(grid[z][x]);
            }
            if (z + 1 < L) printf("\n");
        }
        // blank line between test cases
        printf("\n");
    }
    // end marker
    println(0, 0, 0);
    return 0;
}
