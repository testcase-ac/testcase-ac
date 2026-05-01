#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Board size hyper-parameter
    int R = rnd.next(2, 10);
    int C = rnd.next(2, 10);

    // Generate all cells and shuffle
    vector<pair<int,int>> cells;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());

    // First cell is the player start
    auto ipos = cells[0];

    // Number of crazy Arduinos (0 up to min(R*C-1,10))
    int maxRobots = min((int)cells.size() - 1, 10);
    int K = rnd.next(0, maxRobots);

    // Next K cells are robot positions
    vector<pair<int,int>> robots;
    for (int i = 1; i <= K; i++)
        robots.push_back(cells[i]);

    // Direction deltas for commands '1'..'9'
    vector<int> dr(10), dc(10);
    dr[1] = 1;  dc[1] = -1;
    dr[2] = 1;  dc[2] =  0;
    dr[3] = 1;  dc[3] =  1;
    dr[4] = 0;  dc[4] = -1;
    dr[5] = 0;  dc[5] =  0;
    dr[6] = 0;  dc[6] =  1;
    dr[7] = -1; dc[7] = -1;
    dr[8] = -1; dc[8] =  0;
    dr[9] = -1; dc[9] =  1;
    string allDirs = "123456789";

    // Generate a valid command sequence that never leaves the board
    int L = rnd.next(1, 15);
    string commands;
    int curR = ipos.first, curC = ipos.second;
    for (int step = 0; step < L; step++) {
        // Collect only directions that keep the player in-bounds
        vector<char> opts;
        for (char d : allDirs) {
            int di = d - '0';
            int nr = curR + dr[di];
            int nc = curC + dc[di];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                // Weight '5' (stay) a bit more often
                if (d == '5') {
                    opts.push_back(d);
                    opts.push_back(d);
                } else {
                    opts.push_back(d);
                }
            }
        }
        char pick = rnd.any(opts);
        commands.push_back(pick);
        int pd = pick - '0';
        curR += dr[pd];
        curC += dc[pd];
    }

    // Output
    printf("%d %d\n", R, C);
    vector<string> grid(R, string(C, '.'));
    grid[ipos.first][ipos.second] = 'I';
    for (auto &p : robots)
        grid[p.first][p.second] = 'R';
    for (int i = 0; i < R; i++)
        printf("%s\n", grid[i].c_str());
    printf("%s\n", commands.c_str());

    return 0;
}
