#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const long long kMaxCoord = 1000000000LL;

long long clampCoord(long long value) {
    return max(1LL, min(kMaxCoord, value));
}

pair<long long, long long> randomPointNear(long long baseX, long long baseY, int radius) {
    return {clampCoord(baseX + rnd.next(-radius, radius)),
            clampCoord(baseY + rnd.next(-radius, radius))};
}

void addPoint(set<pair<long long, long long>>& used,
              vector<pair<long long, long long>>& points,
              long long x,
              long long y) {
    pair<long long, long long> point = {x, y};
    if (used.insert(point).second) {
        points.push_back(point);
    }
}

pair<long long, long long> randomInterval(long long center, int span) {
    long long left = clampCoord(center + rnd.next(-span, span));
    long long right = clampCoord(center + rnd.next(-span, span));
    if (left == right) {
        if (right < kMaxCoord) {
            ++right;
        } else {
            --left;
        }
    }
    if (left > right) {
        swap(left, right);
    }
    return {left, right};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int targetN = rnd.next(1, 45);
    int targetP = rnd.next(1, 35);
    long long baseX = rnd.next(2LL, 999999980LL);
    long long baseY = rnd.next(2LL, 999999980LL);

    set<pair<long long, long long>> used;
    vector<pair<long long, long long>> trees;
    vector<vector<long long>> rects;

    if (mode == 0) {
        int width = rnd.next(2, 9);
        int height = rnd.next(2, 9);
        for (int dx = 0; dx < width && (int)trees.size() < targetN; ++dx) {
            for (int dy = 0; dy < height && (int)trees.size() < targetN; ++dy) {
                if (rnd.next(100) < 55) {
                    addPoint(used, trees, baseX + dx, baseY + dy);
                }
            }
        }
        if (trees.empty()) {
            addPoint(used, trees, baseX, baseY);
        }

        for (int i = 0; i < targetP; ++i) {
            long long x1 = baseX + rnd.next(0, max(0, width - 2));
            long long y1 = baseY + rnd.next(0, max(0, height - 2));
            long long x2 = baseX + rnd.next((int)(x1 - baseX + 1), width);
            long long y2 = baseY + rnd.next((int)(y1 - baseY + 1), height);
            rects.push_back({x1, y1, x2, y2});
        }
    } else if (mode == 1) {
        long long x1 = baseX;
        long long y1 = baseY;
        long long x2 = baseX + rnd.next(2, 20);
        long long y2 = baseY + rnd.next(2, 20);

        for (int i = 0; i < targetN; ++i) {
            int side = rnd.next(5);
            if (side == 0) {
                addPoint(used, trees, x1, rnd.next(y1, y2));
            } else if (side == 1) {
                addPoint(used, trees, x2, rnd.next(y1, y2));
            } else if (side == 2) {
                addPoint(used, trees, rnd.next(x1, x2), y1);
            } else if (side == 3) {
                addPoint(used, trees, rnd.next(x1, x2), y2);
            } else {
                addPoint(used, trees, rnd.next(x1 + 1, x2 - 1), rnd.next(y1 + 1, y2 - 1));
            }
        }
        if (trees.empty()) {
            addPoint(used, trees, x1, y1);
        }

        rects.push_back({x1, y1, x2, y2});
        while ((int)rects.size() < targetP) {
            long long shiftX = rnd.next(-3, 3);
            long long shiftY = rnd.next(-3, 3);
            rects.push_back({clampCoord(x1 + shiftX), clampCoord(y1 + shiftY),
                             clampCoord(x2 + shiftX + rnd.next(0, 3)),
                             clampCoord(y2 + shiftY + rnd.next(0, 3))});
            if (rects.back()[0] >= rects.back()[2]) {
                rects.back()[2] = rects.back()[0] + 1;
            }
            if (rects.back()[1] >= rects.back()[3]) {
                rects.back()[3] = rects.back()[1] + 1;
            }
        }
    } else if (mode == 2) {
        vector<long long> xs = {1, 2, kMaxCoord - 1, kMaxCoord};
        vector<long long> ys = {1, 2, kMaxCoord - 1, kMaxCoord};
        for (long long x : xs) {
            for (long long y : ys) {
                if (rnd.next(100) < 70) {
                    addPoint(used, trees, x, y);
                }
            }
        }
        while ((int)trees.size() < targetN) {
            addPoint(used, trees, rnd.any(xs), rnd.next(1LL, kMaxCoord));
        }

        rects.push_back({1, 1, kMaxCoord, kMaxCoord});
        rects.push_back({1, 1, 2, 2});
        rects.push_back({kMaxCoord - 1, kMaxCoord - 1, kMaxCoord, kMaxCoord});
        while ((int)rects.size() < targetP) {
            auto xr = randomInterval(rnd.any(xs), 10);
            auto yr = randomInterval(rnd.any(ys), 10);
            rects.push_back({xr.first, yr.first, xr.second, yr.second});
        }
    } else {
        vector<long long> xs;
        vector<long long> ys;
        int lineCount = rnd.next(7, 10);
        int xStep = rnd.next(1, 4);
        int yStep = rnd.next(1, 4);
        for (int i = 0; i < lineCount; ++i) {
            xs.push_back(baseX + i * xStep);
            ys.push_back(baseY + i * yStep);
        }
        while ((int)trees.size() < targetN) {
            addPoint(used, trees, rnd.any(xs), rnd.any(ys));
        }

        for (int i = 0; i < targetP; ++i) {
            long long x1 = rnd.any(xs);
            long long x2 = rnd.any(xs);
            long long y1 = rnd.any(ys);
            long long y2 = rnd.any(ys);
            if (x1 == x2) {
                x2 = clampCoord(x1 + rnd.next(1, 8));
            }
            if (y1 == y2) {
                y2 = clampCoord(y1 + rnd.next(1, 8));
            }
            if (x1 > x2) {
                swap(x1, x2);
            }
            if (y1 > y2) {
                swap(y1, y2);
            }
            rects.push_back({x1, y1, x2, y2});
        }
    }

    shuffle(trees.begin(), trees.end());
    shuffle(rects.begin(), rects.end());

    println((int)trees.size());
    for (auto [x, y] : trees) {
        println(x, y);
    }
    println((int)rects.size());
    for (const auto& r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }

    return 0;
}
