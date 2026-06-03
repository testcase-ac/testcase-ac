#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static bool validGrid(const vector<string>& grid) {
    vector<pair<int, int>> people;
    vector<pair<int, int>> seats;

    int r = (int)grid.size();
    int c = (int)grid[0].size();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == 'X') {
                people.push_back({i, j});
            } else if (grid[i][j] == 'L') {
                seats.push_back({i, j});
            }
        }
    }

    if (people.empty() || seats.empty()) return false;

    for (auto person : people) {
        vector<int> distances;
        for (auto seat : seats) {
            int dr = person.first - seat.first;
            int dc = person.second - seat.second;
            distances.push_back(dr * dr + dc * dc);
        }
        sort(distances.begin(), distances.end());
        for (int i = 1; i < (int)distances.size(); ++i) {
            if (distances[i - 1] == distances[i]) return false;
        }
    }

    return true;
}

static vector<string> randomGrid(int r, int c, int people, int seats) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    vector<string> grid(r, string(c, '.'));
    int pos = 0;
    for (int i = 0; i < seats; ++i) {
        grid[cells[pos].first][cells[pos].second] = 'L';
        ++pos;
    }
    for (int i = 0; i < people; ++i) {
        grid[cells[pos].first][cells[pos].second] = 'X';
        ++pos;
    }
    return grid;
}

static vector<string> makeLineGrid() {
    int c = rnd.next(2, 16);
    int seats = rnd.next(1, min(5, c - 1));
    int people = rnd.next(1, min(8, c - seats));
    return randomGrid(1, c, people, seats);
}

static vector<string> makeSmallGrid() {
    int r = rnd.next(2, 8);
    int c = rnd.next(2, 8);
    int cells = r * c;
    int seats = rnd.next(1, min(8, cells - 1));
    int people = rnd.next(1, min(12, cells - seats));
    return randomGrid(r, c, people, seats);
}

static vector<string> makeMediumGrid() {
    int r = rnd.next(8, 14);
    int c = rnd.next(8, 14);
    int cells = r * c;
    int seats = rnd.next(3, 14);
    int people = rnd.next(6, min(24, cells - seats));
    return randomGrid(r, c, people, seats);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> grid;
    for (int attempt = 0; attempt < 10000; ++attempt) {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            grid = makeLineGrid();
        } else if (mode == 1) {
            grid = makeSmallGrid();
        } else {
            grid = makeMediumGrid();
        }

        if (validGrid(grid)) break;
    }
    if (!validGrid(grid)) {
        grid = {"XL"};
    }

    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
