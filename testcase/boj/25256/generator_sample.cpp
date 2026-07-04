#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static const string kNeedles = "WALDO";
static const string kFiller = "BCEFGHIJKMNPQRSTUVXYZ";

static vector<string> makeGrid(int h, int w) {
    vector<string> grid(h, string(w, 'B'));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            grid[i][j] = rnd.any(kFiller);
        }
    }
    return grid;
}

static void placeLetters(vector<string>& grid, const string& letters) {
    int h = (int)grid.size();
    int w = (int)grid[0].size();

    vector<pair<int, int>> cells;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    for (int i = 0; i < (int)letters.size(); ++i) {
        grid[cells[i].first][cells[i].second] = letters[i];
    }
}

static vector<string> makeImpossible() {
    int h = rnd.next(1, 8);
    int w = rnd.next(1, 14);
    vector<string> grid = makeGrid(h, w);

    string letters = kNeedles;
    int missing = rnd.next(0, (int)letters.size() - 1);
    letters.erase(letters.begin() + missing);
    int copies = rnd.next(0, min(12, h * w));
    string present;
    for (int i = 0; i < copies; ++i) {
        present += rnd.any(letters);
    }
    placeLetters(grid, present);
    return grid;
}

static vector<string> makeLine() {
    bool horizontal = rnd.next(0, 1) == 0;
    int h = horizontal ? 1 : rnd.next(5, 18);
    int w = horizontal ? rnd.next(5, 24) : 1;
    vector<string> grid = makeGrid(h, w);

    string letters = kNeedles;
    shuffle(letters.begin(), letters.end());
    placeLetters(grid, letters);

    int extra = rnd.next(0, min(8, h * w - 5));
    string noise;
    for (int i = 0; i < extra; ++i) {
        noise += rnd.any(kNeedles);
    }
    placeLetters(grid, noise);
    return grid;
}

static vector<string> makeTightCluster() {
    int h = rnd.next(2, 8);
    int w = rnd.next(3, 10);
    vector<string> grid = makeGrid(h, w);

    int top = rnd.next(0, h - 2);
    int left = rnd.next(0, w - 3);
    vector<pair<int, int>> cells;
    for (int i = top; i <= top + 1; ++i) {
        for (int j = left; j <= left + 2; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    string letters = kNeedles;
    shuffle(letters.begin(), letters.end());
    for (int i = 0; i < 5; ++i) {
        grid[cells[i].first][cells[i].second] = letters[i];
    }

    int extras = rnd.next(0, 10);
    string noise;
    for (int i = 0; i < extras; ++i) {
        noise += rnd.any(kNeedles);
    }
    placeLetters(grid, noise);
    return grid;
}

static vector<string> makeScattered() {
    int h = rnd.next(4, 12);
    int w = rnd.next(4, 16);
    vector<string> grid = makeGrid(h, w);

    vector<pair<int, int>> anchors = {
        {0, 0},
        {0, w - 1},
        {h - 1, 0},
        {h - 1, w - 1},
        {rnd.next(0, h - 1), rnd.next(0, w - 1)},
    };
    shuffle(anchors.begin(), anchors.end());

    string letters = kNeedles;
    shuffle(letters.begin(), letters.end());
    for (int i = 0; i < 5; ++i) {
        grid[anchors[i].first][anchors[i].second] = letters[i];
    }

    int extras = rnd.next(0, 18);
    string noise;
    for (int i = 0; i < extras; ++i) {
        noise += rnd.any(kNeedles);
    }
    placeLetters(grid, noise);
    return grid;
}

static vector<string> makeMedium() {
    int h = rnd.next(8, 20);
    int w = rnd.next(8, 24);
    vector<string> grid = makeGrid(h, w);

    string letters;
    int copies = rnd.next(1, 5);
    for (int i = 0; i < copies; ++i) {
        letters += kNeedles;
    }
    shuffle(letters.begin(), letters.end());
    placeLetters(grid, letters);
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> grid;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        grid = makeImpossible();
    } else if (mode == 1) {
        grid = makeLine();
    } else if (mode == 2) {
        grid = makeTightCluster();
    } else if (mode == 3) {
        grid = makeScattered();
    } else {
        grid = makeMedium();
    }

    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
