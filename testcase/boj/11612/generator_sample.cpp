#include "testlib.h"

#include <utility>
#include <vector>
using namespace std;

struct Gear {
    int x;
    int y;
    int r;
};

void printGears(const vector<Gear>& gears) {
    println(static_cast<int>(gears.size()));
    for (const Gear& gear : gears) {
        println(gear.x, gear.y, gear.r);
    }
}

vector<Gear> makeChain() {
    int n = rnd.next(2, 14);
    vector<Gear> gears;
    gears.reserve(n);

    int x = rnd.next(-80, -20);
    int y = rnd.next(-30, 30);
    int r = rnd.next(1, 9);
    gears.push_back({x, y, r});

    for (int i = 1; i < n; ++i) {
        int nextR = rnd.next(1, 9);
        x += r + nextR;
        gears.push_back({x, y, nextR});
        r = nextR;
    }
    return gears;
}

vector<Gear> makeSeparatedComponents() {
    int leftCount = rnd.next(1, 6);
    int rightCount = rnd.next(1, 6);
    vector<Gear> gears;

    int x = -250;
    int y = rnd.next(-20, 20);
    int r = rnd.next(1, 8);
    gears.push_back({x, y, r});
    for (int i = 1; i < leftCount; ++i) {
        int nextR = rnd.next(1, 8);
        x += r + nextR;
        gears.push_back({x, y, nextR});
        r = nextR;
    }

    x = 250;
    y = rnd.next(-20, 20);
    r = rnd.next(1, 8);
    for (int i = 0; i < rightCount; ++i) {
        if (i > 0) {
            int nextR = rnd.next(1, 8);
            x += r + nextR;
            r = nextR;
        }
        gears.push_back({x, y, r});
    }

    return gears;
}

vector<Gear> makeOddCycle() {
    int scale = rnd.next(1, 12);
    vector<Gear> gears = {
        {0, 0, scale},
        {0, 3 * scale, 2 * scale},
        {4 * scale, 0, 3 * scale},
    };

    int tail = rnd.next(0, 6);
    int x = 4 * scale;
    int y = 0;
    int r = 3 * scale;
    for (int i = 0; i < tail; ++i) {
        int nextR = rnd.next(1, 8);
        x += r + nextR;
        gears.push_back({x, y, nextR});
        r = nextR;
    }
    return gears;
}

vector<Gear> makeGrid() {
    int rows = rnd.next(2, 4);
    int cols = rnd.next(2, 5);
    int r = rnd.next(1, 7);
    vector<pair<int, int>> cells;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            cells.push_back({row, col});
        }
    }
    shuffle(cells.begin(), cells.end());

    int keep = rnd.next(2, static_cast<int>(cells.size()));
    vector<Gear> gears;
    gears.reserve(keep);
    for (int i = 0; i < keep; ++i) {
        int row = cells[i].first;
        int col = cells[i].second;
        gears.push_back({2 * r * col, 2 * r * row, r});
    }
    return gears;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    if (mode == 0) {
        printGears(makeChain());
    } else if (mode == 1) {
        printGears(makeSeparatedComponents());
    } else if (mode == 2) {
        printGears(makeOddCycle());
    } else {
        printGears(makeGrid());
    }

    return 0;
}
