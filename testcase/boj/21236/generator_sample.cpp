#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addCell(vector<pair<int, int>>& cells, set<pair<int, int>>& used, int x, int y) {
    if (0 <= x && x <= 1000 && 0 <= y && y <= 1000 && used.insert({x, y}).second) {
        cells.push_back({x, y});
    }
}

void addPlus(vector<pair<int, int>>& cells, set<pair<int, int>>& used, int x, int y) {
    addCell(cells, used, x, y);
    vector<pair<int, int>> neighbors = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
    shuffle(neighbors.begin(), neighbors.end());

    int take = rnd.next(3, 4);
    for (int i = 0; i < take; ++i) {
        addCell(cells, used, neighbors[i].first, neighbors[i].second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cells;
    set<pair<int, int>> used;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int groups = rnd.next(1, 8);
        for (int g = 0; g < groups; ++g) {
            int x = rnd.next(2, 998);
            int y = rnd.next(2, 998);
            addPlus(cells, used, x, y);
        }
    } else if (mode == 1) {
        int width = rnd.next(2, 9);
        int height = rnd.next(2, 9);
        int ox = rnd.next(0, 1000 - width);
        int oy = rnd.next(0, 1000 - height);
        vector<pair<int, int>> block;
        for (int dx = 0; dx < width; ++dx) {
            for (int dy = 0; dy < height; ++dy) {
                block.push_back({ox + dx, oy + dy});
            }
        }
        shuffle(block.begin(), block.end());

        int take = rnd.next(1, (int)block.size());
        for (int i = 0; i < take; ++i) {
            addCell(cells, used, block[i].first, block[i].second);
        }
    } else if (mode == 2) {
        int length = rnd.next(4, 30);
        int x = rnd.next(1, 999);
        int y = rnd.next(1, 999);
        bool horizontal = rnd.next(0, 1);
        for (int i = 0; i < length; ++i) {
            addCell(cells, used, x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
            if (rnd.next(0, 2) == 0) {
                addCell(cells, used, x + (horizontal ? i : rnd.next(-1, 1)),
                        y + (horizontal ? rnd.next(-1, 1) : i));
            }
        }
    } else if (mode == 3) {
        vector<pair<int, int>> corners = {{0, 0}, {0, 1000}, {1000, 0}, {1000, 1000}};
        shuffle(corners.begin(), corners.end());
        int around = rnd.next(1, 4);
        for (int i = 0; i < around; ++i) {
            int x = corners[i].first;
            int y = corners[i].second;
            addCell(cells, used, x, y);
            addCell(cells, used, x == 0 ? 1 : 999, y);
            addCell(cells, used, x, y == 0 ? 1 : 999);
        }
    } else {
        int n = rnd.next(1, 80);
        int ox = rnd.next(0, 985);
        int oy = rnd.next(0, 985);
        while ((int)cells.size() < n) {
            addCell(cells, used, ox + rnd.next(0, 15), oy + rnd.next(0, 15));
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(cells.begin(), cells.end());
    }

    println((int)cells.size());
    for (auto [x, y] : cells) {
        println(x, y);
    }

    return 0;
}
