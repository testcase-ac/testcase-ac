#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomCost(int low = 1, int high = 9) {
    return char('0' + rnd.next(low, high));
}

void printGrid(const vector<string>& grid) {
    println((int)grid[0].size(), (int)grid.size());
    for (const string& row : grid) {
        for (int x = 0; x < (int)row.size(); ++x) {
            if (x) cout << ' ';
            cout << row[x];
        }
        cout << '\n';
    }
}

vector<string> makeOpenGrid(int w, int h) {
    vector<string> grid(h, string(w, '1'));
    for (int y = 1; y + 1 < h; ++y) {
        for (int x = 0; x < w; ++x) {
            grid[y][x] = randomCost(1, 9);
        }
    }
    for (int x = 0; x < w; ++x) {
        grid[0][x] = rnd.next(100) < 45 ? 'T' : randomCost(1, 9);
        grid[h - 1][x] = rnd.next(100) < 55 ? 'S' : randomCost(1, 9);
    }
    grid[0][rnd.next(w)] = 'T';
    grid[h - 1][rnd.next(w)] = 'S';
    return grid;
}

vector<string> makeNarrowGrid(int w, int h) {
    vector<string> grid(h, string(w, 'X'));
    int col = rnd.next(w);
    grid[0][col] = 'T';
    grid[h - 1][col] = 'S';
    for (int y = 1; y + 1 < h; ++y) {
        grid[y][col] = randomCost(1, 9);
        if (w > 2 && rnd.next(100) < 55) {
            int side = col + rnd.any(vector<int>{-1, 1});
            if (0 <= side && side < w) grid[y][side] = randomCost(1, 9);
        }
    }
    if (w > 2 && rnd.next(2)) {
        int other = rnd.next(w);
        grid[h - 1][other] = 'S';
    }
    return grid;
}

vector<string> makeBlockedGrid(int w, int h) {
    vector<string> grid = makeOpenGrid(w, h);
    int blockChance = rnd.next(25, 65);
    for (int y = 1; y + 1 < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (rnd.next(100) < blockChance) grid[y][x] = 'X';
        }
    }
    int carved = rnd.next(1, min(w, 4));
    for (int i = 0; i < carved; ++i) {
        int col = rnd.next(w);
        for (int y = 1; y + 1 < h; ++y) {
            if (rnd.next(100) < 75) grid[y][col] = randomCost(1, 9);
        }
        grid[0][col] = 'T';
        grid[h - 1][col] = 'S';
    }
    return grid;
}

vector<string> makeStripedGrid(int w, int h) {
    vector<string> grid(h, string(w, '1'));
    for (int y = 1; y + 1 < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if ((x + y + rnd.next(3)) % 4 == 0) {
                grid[y][x] = 'X';
            } else {
                grid[y][x] = char('1' + ((x * 2 + y + rnd.next(3)) % 9));
            }
        }
    }
    for (int x = 0; x < w; ++x) {
        grid[0][x] = (x % 3 == 0 || rnd.next(100) < 20) ? 'T' : randomCost(1, 9);
        grid[h - 1][x] = (x % 2 == 0 || rnd.next(100) < 20) ? 'S' : randomCost(1, 9);
    }
    grid[0][rnd.next(w)] = 'T';
    grid[h - 1][rnd.next(w)] = 'S';
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(3, 7);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = rnd.next(4);
        int w = rnd.next(2, 12);
        int h = rnd.next(5, 16);

        if (mode == 0) {
            printGrid(makeNarrowGrid(w, h));
        } else if (mode == 1) {
            printGrid(makeOpenGrid(w, h));
        } else if (mode == 2) {
            printGrid(makeBlockedGrid(w, h));
        } else {
            printGrid(makeStripedGrid(w, h));
        }
    }
    println(0, 0);

    return 0;
}
