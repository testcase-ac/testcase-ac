#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int length;
    int width;
    vector<string> grid;
};

char clearCell() {
    return rnd.next(0, 1) == 0 ? 'G' : 'S';
}

char obstacleCell() {
    static const string obstacles = "RWT";
    return obstacles[rnd.next((int)obstacles.size())];
}

CaseData makeCase(int mode) {
    int length = rnd.next(1, 18);
    int width = rnd.next(1, 18);
    if (mode == 5) {
        length = rnd.next(20, 50);
        width = rnd.next(12, 35);
    }

    vector<string> grid(width, string(length, 'G'));
    for (int r = 0; r < width; ++r) {
        for (int c = 0; c < length; ++c) {
            grid[r][c] = clearCell();
        }
    }

    vector<pair<int, int>> cells;
    for (int r = 0; r < width; ++r) {
        for (int c = 0; c < length; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    int obstacleLimit = min(19, length * width);
    int placed = 0;
    auto place = [&](int r, int c) {
        if (placed >= obstacleLimit || grid[r][c] == 'R' || grid[r][c] == 'W' || grid[r][c] == 'T') {
            return;
        }
        grid[r][c] = obstacleCell();
        ++placed;
    };

    if (mode == 0) {
        return {length, width, grid};
    }

    if (mode == 1) {
        int count = rnd.next(1, min(obstacleLimit, 8));
        for (int i = 0; i < count; ++i) {
            place(cells[i].first, cells[i].second);
        }
    } else if (mode == 2) {
        int row = rnd.next(width);
        int gapLeft = rnd.next(length);
        int gapRight = rnd.next(gapLeft, length - 1);
        for (int c = 0; c < length; ++c) {
            if (c < gapLeft || c > gapRight) {
                place(row, c);
            }
        }
    } else if (mode == 3) {
        int col = rnd.next(length);
        int gapTop = rnd.next(width);
        int gapBottom = rnd.next(gapTop, width - 1);
        for (int r = 0; r < width; ++r) {
            if (r < gapTop || r > gapBottom) {
                place(r, col);
            }
        }
    } else if (mode == 4) {
        place(0, 0);
        place(0, length - 1);
        place(width - 1, 0);
        place(width - 1, length - 1);
        int extra = rnd.next(0, min(obstacleLimit - placed, 7));
        for (int i = 0; i < extra; ++i) {
            place(cells[i].first, cells[i].second);
        }
    } else {
        int count = rnd.next(9, obstacleLimit);
        for (int i = 0; i < count; ++i) {
            place(cells[i].first, cells[i].second);
        }
    }

    return {length, width, grid};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(6, 12);
    println(cases);
    for (int tc = 0; tc < cases; ++tc) {
        CaseData data = makeCase(tc % 6);
        println(data.length, data.width);
        for (const string& row : data.grid) {
            println(row);
        }
    }

    return 0;
}
