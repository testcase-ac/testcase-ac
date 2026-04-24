#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int M = rnd.next(2, 8);
    int N = rnd.next(2, 8);
    int H = rnd.next(1, 4);
    // Scenario: 0 = all ripe (with empties), 1 = all unripe (with empties), 2 = mixed
    int scenario = rnd.next(0, 2);
    int empty_pct = rnd.next(0, 30); // percentage of empty cells
    vector<vector<vector<int>>> grid(H, vector<vector<int>>(N, vector<int>(M)));
    // Fill
    if (scenario == 0) {
        // all ripe + empties
        for (int z = 0; z < H; z++)
            for (int y = 0; y < N; y++)
                for (int x = 0; x < M; x++) {
                    int r = rnd.next(100);
                    grid[z][y][x] = (r < empty_pct ? -1 : 1);
                }
        // ensure at least one ripe
        bool any1 = false;
        for (int z = 0; z < H && !any1; z++)
            for (int y = 0; y < N && !any1; y++)
                for (int x = 0; x < M; x++)
                    if (grid[z][y][x] == 1) any1 = true;
        if (!any1) {
            int zi = rnd.next(0, H - 1), yi = rnd.next(0, N - 1), xi = rnd.next(0, M - 1);
            grid[zi][yi][xi] = 1;
        }
    } else if (scenario == 1) {
        // all unripe + empties
        for (int z = 0; z < H; z++)
            for (int y = 0; y < N; y++)
                for (int x = 0; x < M; x++) {
                    int r = rnd.next(100);
                    grid[z][y][x] = (r < empty_pct ? -1 : 0);
                }
        // ensure at least one unripe
        bool any0 = false;
        for (int z = 0; z < H && !any0; z++)
            for (int y = 0; y < N && !any0; y++)
                for (int x = 0; x < M; x++)
                    if (grid[z][y][x] == 0) any0 = true;
        if (!any0) {
            int zi = rnd.next(0, H - 1), yi = rnd.next(0, N - 1), xi = rnd.next(0, M - 1);
            grid[zi][yi][xi] = 0;
        }
    } else {
        // mixed: empties, ripe, unripe
        int ripe_pct = rnd.next(10, 60);
        for (int z = 0; z < H; z++)
            for (int y = 0; y < N; y++)
                for (int x = 0; x < M; x++) {
                    int r = rnd.next(100);
                    if (r < empty_pct) grid[z][y][x] = -1;
                    else if (r < empty_pct + ripe_pct) grid[z][y][x] = 1;
                    else grid[z][y][x] = 0;
                }
        // collect non-empty
        vector<tuple<int,int,int>> zeros, ones, cells;
        for (int z = 0; z < H; z++)
            for (int y = 0; y < N; y++)
                for (int x = 0; x < M; x++) {
                    if (grid[z][y][x] == 0) zeros.emplace_back(z,y,x);
                    if (grid[z][y][x] == 1) ones.emplace_back(z,y,x);
                    if (grid[z][y][x] != -1) cells.emplace_back(z,y,x);
                }
        if (!cells.empty()) {
            if (ones.empty()) {
                auto t = cells[rnd.next(0, (int)cells.size() - 1)];
                grid[get<0>(t)][get<1>(t)][get<2>(t)] = 1;
            }
            if (zeros.empty()) {
                auto t = cells[rnd.next(0, (int)cells.size() - 1)];
                grid[get<0>(t)][get<1>(t)][get<2>(t)] = 0;
            }
        }
    }
    // Print
    println(M, N, H);
    for (int z = 0; z < H; z++) {
        for (int y = 0; y < N; y++) {
            println(grid[z][y]);
        }
    }
    return 0;
}
