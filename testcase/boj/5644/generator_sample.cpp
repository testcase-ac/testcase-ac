#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int H = 20;
const int W = 20;

vector<pair<int, int>> factorShapes(int area) {
    vector<pair<int, int>> shapes;
    for (int h = 1; h <= area; ++h) {
        if (area % h == 0) {
            int w = area / h;
            if (h <= H && w <= W) {
                shapes.push_back({h, w});
            }
        }
    }
    return shapes;
}

vector<int> randomPartition25() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return {25};
    }
    if (mode == 1) {
        vector<int> parts = {5, 5, 5, 5, 5};
        shuffle(parts.begin(), parts.end());
        return parts;
    }
    if (mode == 2) {
        vector<int> parts = {10, 10, 5};
        shuffle(parts.begin(), parts.end());
        return parts;
    }
    if (mode == 3) {
        vector<int> parts = {12, 8, 4, 1};
        shuffle(parts.begin(), parts.end());
        return parts;
    }

    int k = rnd.next(2, 5);
    vector<int> cuts;
    while ((int)cuts.size() < k - 1) {
        int x = rnd.next(1, 24);
        if (find(cuts.begin(), cuts.end(), x) == cuts.end()) {
            cuts.push_back(x);
        }
    }
    sort(cuts.begin(), cuts.end());

    vector<int> parts;
    int prev = 0;
    for (int cut : cuts) {
        parts.push_back(cut - prev);
        prev = cut;
    }
    parts.push_back(25 - prev);
    shuffle(parts.begin(), parts.end());
    return parts;
}

bool canPlace(const vector<string>& grid, int r, int c, int h, int w) {
    for (int rr = r - 1; rr <= r + h; ++rr) {
        for (int cc = c - 1; cc <= c + w; ++cc) {
            if (rr < 0 || rr >= H || cc < 0 || cc >= W) {
                continue;
            }
            if (grid[rr][cc] == 'x') {
                return false;
            }
        }
    }
    return true;
}

vector<string> buildCase() {
    for (int attempt = 0; attempt < 200; ++attempt) {
        vector<string> grid(H, string(W, '.'));
        vector<int> areas = randomPartition25();
        bool ok = true;

        for (int area : areas) {
            vector<pair<int, int>> shapes = factorShapes(area);
            shuffle(shapes.begin(), shapes.end());

            bool placed = false;
            for (int shapeTry = 0; shapeTry < (int)shapes.size() && !placed; ++shapeTry) {
                int h = shapes[shapeTry].first;
                int w = shapes[shapeTry].second;
                if (rnd.next(0, 1)) {
                    swap(h, w);
                }

                for (int posTry = 0; posTry < 200 && !placed; ++posTry) {
                    int r = rnd.next(0, H - h);
                    int c = rnd.next(0, W - w);
                    if (!canPlace(grid, r, c, h, w)) {
                        continue;
                    }

                    for (int rr = r; rr < r + h; ++rr) {
                        for (int cc = c; cc < c + w; ++cc) {
                            grid[rr][cc] = 'x';
                        }
                    }
                    placed = true;
                }
            }

            if (!placed) {
                ok = false;
                break;
            }
        }

        if (ok) {
            return grid;
        }
    }

    vector<string> fallback(H, string(W, '.'));
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            fallback[r][c] = 'x';
        }
    }
    return fallback;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        println("");
        vector<string> grid = buildCase();
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
