#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<string> blankGrid(int r, int c) {
    return vector<string>(r, string(c, '?'));
}

vector<char> shuffledLetters() {
    vector<char> letters;
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        letters.push_back(ch);
    }
    shuffle(letters.begin(), letters.end());
    return letters;
}

void placeLetters(vector<string>& grid, int count) {
    int r = (int)grid.size();
    int c = (int)grid[0].size();

    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    vector<char> letters = shuffledLetters();
    count = min(count, (int)min(cells.size(), letters.size()));
    for (int i = 0; i < count; ++i) {
        grid[cells[i].first][cells[i].second] = letters[i];
    }
}

vector<string> makeCase() {
    int mode = rnd.next(0, 5);
    int r = 1;
    int c = 1;
    vector<string> grid;

    if (mode == 0) {
        r = rnd.next(1, 2);
        c = rnd.next(1, 2);
        grid = blankGrid(r, c);
        placeLetters(grid, 1);
    } else if (mode == 1) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
        grid = blankGrid(r, c);
        int letters = rnd.next(1, min(6, r * c));
        placeLetters(grid, letters);
    } else if (mode == 2) {
        r = rnd.next(4, 12);
        c = rnd.next(4, 12);
        grid = blankGrid(r, c);
        vector<pair<int, int>> anchors = {
            {0, 0},
            {0, c - 1},
            {r - 1, 0},
            {r - 1, c - 1},
            {rnd.next(0, r - 1), rnd.next(0, c - 1)},
        };
        shuffle(anchors.begin(), anchors.end());

        vector<char> letters = shuffledLetters();
        set<pair<int, int>> used;
        int want = rnd.next(2, min(5, r * c));
        int placed = 0;
        for (auto cell : anchors) {
            if (placed == want) {
                break;
            }
            if (used.insert(cell).second) {
                grid[cell.first][cell.second] = letters[placed++];
            }
        }
        while (placed < want) {
            int i = rnd.next(0, r - 1);
            int j = rnd.next(0, c - 1);
            if (used.insert({i, j}).second) {
                grid[i][j] = letters[placed++];
            }
        }
    } else if (mode == 3) {
        r = rnd.next(1, 6);
        c = rnd.next(8, 25);
        grid = blankGrid(r, c);
        int letters = rnd.next(1, min(10, r * c));
        placeLetters(grid, letters);
    } else if (mode == 4) {
        r = rnd.next(8, 25);
        c = rnd.next(1, 6);
        grid = blankGrid(r, c);
        int letters = rnd.next(1, min(10, r * c));
        placeLetters(grid, letters);
    } else {
        r = rnd.next(3, 6);
        c = rnd.next(3, 6);
        grid = blankGrid(r, c);
        int letters = min(26, r * c);
        placeLetters(grid, letters);
        double eraseProbability = rnd.next(0.0, 0.35);
        int remaining = letters;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j] != '?' && remaining > 1 && rnd.next() < eraseProbability) {
                    grid[i][j] = '?';
                    --remaining;
                }
            }
        }
    }

    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        vector<string> grid = makeCase();
        println((int)grid.size(), (int)grid[0].size());
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
