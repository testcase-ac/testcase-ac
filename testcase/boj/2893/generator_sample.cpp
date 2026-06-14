#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Triangle {
    int x;
    int y;
    int r;
};

static int clampCoord(int v) {
    return max(1, min(1000000, v));
}

static Triangle triangleNear(int baseX, int baseY, int baseR, int spread) {
    int x = clampCoord(baseX + rnd.next(-spread, spread));
    int y = clampCoord(baseY + rnd.next(-spread, spread));
    int r = clampCoord(baseR + rnd.next(-spread, spread));
    return {x, y, r};
}

static vector<Triangle> makeDuplicateCase() {
    int n = rnd.next(2, 10);
    Triangle t = {rnd.next(1, 1000000), rnd.next(1, 1000000), rnd.next(1, 1000000)};
    return vector<Triangle>(n, t);
}

static vector<Triangle> makeClusterCase() {
    int n = rnd.next(3, 10);
    int baseX = rnd.next(1, 200);
    int baseY = rnd.next(1, 200);
    int baseR = rnd.next(20, 400);
    int spread = rnd.next(1, 80);

    vector<Triangle> triangles;
    for (int i = 0; i < n; ++i) {
        triangles.push_back(triangleNear(baseX, baseY, baseR, spread));
    }
    return triangles;
}

static vector<Triangle> makeSeparatedCase() {
    int n = rnd.next(1, 10);
    vector<Triangle> triangles;
    int step = rnd.next(5000, 20000);
    int rMax = rnd.next(1, step / 4);
    for (int i = 0; i < n; ++i) {
        int x = clampCoord(1 + i * step + rnd.next(0, step / 8));
        int y = clampCoord(1 + i * step + rnd.next(0, step / 8));
        int r = rnd.next(1, rMax);
        triangles.push_back({x, y, r});
    }
    return triangles;
}

static vector<Triangle> makeDiagonalOverlapCase() {
    int n = rnd.next(4, 10);
    int x = rnd.next(1, 1000);
    int y = rnd.next(1, 1000);
    int r = rnd.next(50, 1000);

    vector<Triangle> triangles;
    for (int i = 0; i < n; ++i) {
        int delta = rnd.next(0, r);
        int xi = clampCoord(x + delta + rnd.next(0, 5));
        int yi = clampCoord(y + rnd.next(0, max(1, r / 3)));
        int ri = clampCoord(r - delta / 2 + rnd.next(-10, 10));
        triangles.push_back({xi, yi, ri});
    }
    return triangles;
}

static vector<Triangle> makeLimitCase() {
    int n = rnd.next(3, 10);
    vector<Triangle> triangles;
    for (int i = 0; i < n; ++i) {
        int x = rnd.next(0, 1) == 0 ? rnd.next(1, 20) : rnd.next(999980, 1000000);
        int y = rnd.next(0, 1) == 0 ? rnd.next(1, 20) : rnd.next(999980, 1000000);
        int r = rnd.next(0, 1) == 0 ? rnd.next(1, 20) : rnd.next(999980, 1000000);
        triangles.push_back({x, y, r});
    }
    return triangles;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Triangle> triangles;
    if (mode == 0) {
        triangles = makeDuplicateCase();
    } else if (mode == 1) {
        triangles = makeClusterCase();
    } else if (mode == 2) {
        triangles = makeSeparatedCase();
    } else if (mode == 3) {
        triangles = makeDiagonalOverlapCase();
    } else {
        triangles = makeLimitCase();
    }

    if (rnd.next(0, 1) == 1) shuffle(triangles.begin(), triangles.end());

    println((int)triangles.size());
    for (const Triangle& t : triangles) {
        println(t.x, t.y, t.r);
    }

    return 0;
}
