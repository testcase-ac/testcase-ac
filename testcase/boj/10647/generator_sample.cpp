#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shapeMode = rnd.next(0, 5);
    int r;
    int s;
    if (shapeMode == 0) {
        r = 1;
        s = rnd.next(1, 20);
    } else if (shapeMode == 1) {
        r = rnd.next(1, 20);
        s = 1;
    } else if (shapeMode == 2) {
        r = rnd.next(2, 5);
        s = rnd.next(2, 5);
    } else if (shapeMode == 3) {
        r = rnd.next(6, 12);
        s = rnd.next(6, 12);
    } else if (shapeMode == 4) {
        r = rnd.next(2, 8);
        s = rnd.next(12, 25);
    } else {
        r = rnd.next(12, 25);
        s = rnd.next(2, 8);
    }

    vector<string> garden(r, string(s, '.'));
    int treeMode = rnd.next(0, 4);
    if (treeMode == 0) {
        garden[rnd.next(0, r - 1)][rnd.next(0, s - 1)] = 'x';
    } else if (treeMode == 1) {
        vector<pair<int, int>> corners = {
            {0, 0}, {0, s - 1}, {r - 1, 0}, {r - 1, s - 1},
        };
        shuffle(corners.begin(), corners.end());
        int take = rnd.next(1, (int)corners.size());
        for (int i = 0; i < take; ++i) {
            garden[corners[i].first][corners[i].second] = 'x';
        }
    } else {
        int percent = treeMode == 2 ? rnd.next(8, 25) : rnd.next(35, 70);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < s; ++j) {
                if (rnd.next(1, 100) <= percent) {
                    garden[i][j] = 'x';
                }
            }
        }
    }
    if (count(garden.begin(), garden.end(), string(s, '.')) == r) {
        garden[rnd.next(0, r - 1)][rnd.next(0, s - 1)] = 'x';
    }

    int g = rnd.next(1, min(80, max(1, r * s * 2)));
    int queryMode = rnd.next(0, 4);
    vector<pair<int, int>> falls;
    falls.reserve(g);

    if (queryMode == 0) {
        int row = rnd.next(1, r);
        for (int i = 0; i < g; ++i) {
            falls.push_back({row, rnd.next(1, s)});
        }
    } else if (queryMode == 1) {
        int col = rnd.next(1, s);
        for (int i = 0; i < g; ++i) {
            falls.push_back({rnd.next(1, r), col});
        }
    } else if (queryMode == 2) {
        int centerR = rnd.next(1, r);
        int centerS = rnd.next(1, s);
        for (int i = 0; i < g; ++i) {
            int dr = rnd.next(-2, 2);
            int ds = rnd.next(-2, 2);
            int row = min(r, max(1, centerR + dr));
            int col = min(s, max(1, centerS + ds));
            falls.push_back({row, col});
        }
    } else if (queryMode == 3) {
        vector<pair<int, int>> candidates = {
            {1, 1}, {1, s}, {r, 1}, {r, s},
        };
        for (int i = 0; i < g; ++i) {
            falls.push_back(rnd.any(candidates));
        }
    } else {
        for (int i = 0; i < g; ++i) {
            falls.push_back({rnd.next(1, r), rnd.next(1, s)});
        }
    }

    println(r, s);
    for (const string& row : garden) {
        println(row);
    }
    println(g);
    for (const auto& fall : falls) {
        println(fall.first, fall.second);
    }

    return 0;
}
