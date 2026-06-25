#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct CaseInput {
    int r;
    int c;
    int n;
};

static vector<pair<int, int>> allShapes() {
    vector<pair<int, int>> shapes;
    for (int r = 1; r <= 16; ++r) {
        for (int c = 1; c <= 16; ++c) {
            if (r * c <= 16) {
                shapes.push_back({r, c});
            }
        }
    }
    return shapes;
}

static int chooseTenantCount(int cells, int mode) {
    int halfLow = cells / 2;
    int halfHigh = (cells + 1) / 2;

    if (mode == 0) return 0;
    if (mode == 1) return cells;
    if (mode == 2) return rnd.next(0, halfHigh);
    if (mode == 3) return rnd.next(halfLow, cells);
    if (mode == 4) return max(0, halfHigh - rnd.next(0, min(2, halfHigh)));
    if (mode == 5) return min(cells, halfHigh + rnd.next(0, min(3, cells - halfHigh)));
    return rnd.next(0, cells);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> shapes = allShapes();
    vector<CaseInput> cases;

    int t = rnd.next(8, 24);
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        pair<int, int> shape;
        int shapeMode = rnd.next(0, 5);
        if (shapeMode == 0) {
            int cells = rnd.next(1, 16);
            shape = rnd.next(0, 1) == 0 ? make_pair(1, cells) : make_pair(cells, 1);
        } else if (shapeMode == 1) {
            shape = rnd.any(vector<pair<int, int>>{{2, 2}, {2, 3}, {3, 2}, {2, 4}, {4, 2}, {3, 3}, {4, 4}});
        } else {
            shape = rnd.any(shapes);
        }

        int cells = shape.first * shape.second;
        int n = chooseTenantCount(cells, rnd.next(0, 6));
        cases.push_back({shape.first, shape.second, n});
    }

    println(t);
    for (const CaseInput& testCase : cases) {
        println(testCase.r, testCase.c, testCase.n);
    }

    return 0;
}
