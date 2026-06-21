#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int w = rnd.next(3, 14);
    int h = rnd.next(3, 12);
    if (mode == 0) {
        w = rnd.next(3, 6);
        h = rnd.next(3, 6);
    } else if (mode == 4) {
        w = rnd.next(10, 18);
        h = rnd.next(8, 14);
    }

    vector<string> grid(h, string(w, '.'));
    for (int y = 0; y < h; ++y) {
        grid[y][0] = '#';
        grid[y][w - 1] = '#';
    }
    for (int x = 0; x < w; ++x) {
        grid[0][x] = '#';
        grid[h - 1][x] = '#';
    }

    vector<pair<int, int>> cells;
    for (int y = 1; y + 1 < h; ++y) {
        for (int x = 1; x + 1 < w; ++x) {
            cells.push_back({y, x});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> player = cells[0];
    grid[player.first][player.second] = 'P';

    int wallPercent = 0;
    int trapPercent = 12;
    int goldPercent = 22;
    if (mode == 0) {
        wallPercent = 0;
        trapPercent = rnd.next(0, 20);
        goldPercent = rnd.next(0, 45);
    } else if (mode == 1) {
        wallPercent = rnd.next(5, 20);
        trapPercent = rnd.next(0, 12);
        goldPercent = rnd.next(15, 35);
    } else if (mode == 2) {
        wallPercent = rnd.next(0, 8);
        trapPercent = rnd.next(20, 40);
        goldPercent = rnd.next(10, 30);
    } else if (mode == 3) {
        wallPercent = rnd.next(20, 40);
        trapPercent = rnd.next(5, 20);
        goldPercent = rnd.next(5, 25);
    } else {
        wallPercent = rnd.next(8, 25);
        trapPercent = rnd.next(8, 25);
        goldPercent = rnd.next(20, 45);
    }

    for (size_t i = 1; i < cells.size(); ++i) {
        int y = cells[i].first;
        int x = cells[i].second;
        int roll = rnd.next(1, 100);
        if (roll <= wallPercent) {
            grid[y][x] = '#';
        } else if (roll <= wallPercent + trapPercent) {
            grid[y][x] = 'T';
        } else if (roll <= wallPercent + trapPercent + goldPercent) {
            grid[y][x] = 'G';
        }
    }

    if (mode == 1 || mode == 2) {
        static const int dy[4] = {-1, 1, 0, 0};
        static const int dx[4] = {0, 0, -1, 1};
        int drafts = rnd.next(1, 4);
        for (int k = 0; k < drafts; ++k) {
            int dir = rnd.next(0, 3);
            int ny = player.first + dy[dir];
            int nx = player.second + dx[dir];
            if (ny > 0 && ny + 1 < h && nx > 0 && nx + 1 < w) {
                grid[ny][nx] = 'T';
            }
        }
    }

    println(w, h);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
