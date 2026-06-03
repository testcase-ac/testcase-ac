#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Target {
    string kind;
    int a;
    int b;
    int c;
    int d;
};

int clampCoord(int value) {
    return max(-1000, min(1000, value));
}

Target rectangleTarget(int x1, int y1, int x2, int y2) {
    x1 = clampCoord(x1);
    y1 = clampCoord(y1);
    x2 = clampCoord(x2);
    y2 = clampCoord(y2);
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    if (x1 == x2) {
        if (x2 < 1000) ++x2;
        else --x1;
    }
    if (y1 == y2) {
        if (y2 < 1000) ++y2;
        else --y1;
    }
    return {"rectangle", x1, y1, x2, y2};
}

Target circleTarget(int x, int y, int r) {
    return {"circle", clampCoord(x), clampCoord(y), max(1, min(1000, r)), 0};
}

void addShot(vector<pair<int, int>>& shots, int x, int y) {
    shots.push_back({clampCoord(x), clampCoord(y)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Target> targets;
    vector<pair<int, int>> shots;
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        int baseX = rnd.next(-20, 20);
        int baseY = rnd.next(-20, 20);
        int count = rnd.next(4, 10);

        for (int i = 0; i < count; ++i) {
            if (i % 2 == 0) {
                int w = rnd.next(1, 15);
                int h = rnd.next(1, 15);
                int x1 = baseX + rnd.next(-12, 8);
                int y1 = baseY + rnd.next(-12, 8);
                targets.push_back(rectangleTarget(x1, y1, x1 + w, y1 + h));
            } else {
                targets.push_back(circleTarget(baseX + rnd.next(-10, 10),
                                               baseY + rnd.next(-10, 10),
                                               rnd.next(1, 18)));
            }
        }

        for (int dx : {-15, -1, 0, 1, 15}) {
            for (int dy : {-15, 0, 15}) {
                if (rnd.next(0, 1)) addShot(shots, baseX + dx, baseY + dy);
            }
        }
    } else if (mode == 1) {
        targets.push_back(rectangleTarget(-1000, -1000, 1000, 1000));
        targets.push_back(rectangleTarget(-1000,
                                          rnd.next(-1000, -990),
                                          rnd.next(-990, -900),
                                          1000));
        targets.push_back(rectangleTarget(rnd.next(900, 990),
                                          -1000,
                                          1000,
                                          rnd.next(990, 1000)));
        targets.push_back(circleTarget(-1000, 1000, rnd.next(1, 1000)));
        targets.push_back(circleTarget(1000, -1000, rnd.next(1, 1000)));

        addShot(shots, -1000, -1000);
        addShot(shots, 1000, 1000);
        addShot(shots, -1000, 1000);
        addShot(shots, 1000, -1000);
        addShot(shots, 0, 0);
        for (int i = 0; i < rnd.next(2, 8); ++i) {
            addShot(shots, rnd.next(-1000, 1000), rnd.next(-1000, 1000));
        }
    } else if (mode == 2) {
        int x1 = rnd.next(-50, 20);
        int y1 = rnd.next(-50, 20);
        int x2 = x1 + rnd.next(1, 30);
        int y2 = y1 + rnd.next(1, 30);
        targets.push_back(rectangleTarget(x1, y1, x2, y2));
        targets.push_back(rectangleTarget(x1 - rnd.next(0, 5),
                                          y1 - rnd.next(0, 5),
                                          x2 + rnd.next(0, 5),
                                          y2 + rnd.next(0, 5)));
        targets.push_back(circleTarget(x1, y1, rnd.next(1, 20)));
        targets.push_back(circleTarget(x2, y2, rnd.next(1, 20)));

        addShot(shots, x1, y1);
        addShot(shots, x2, y2);
        addShot(shots, x1, y2);
        addShot(shots, x2, y1);
        addShot(shots, x1 - 1, y1);
        addShot(shots, x2 + 1, y2);
        addShot(shots, (x1 + x2) / 2, (y1 + y2) / 2);
    } else {
        int count = rnd.next(1, 30);
        for (int i = 0; i < count; ++i) {
            if (rnd.next(0, 1)) {
                int x1 = rnd.next(-1000, 999);
                int y1 = rnd.next(-1000, 999);
                int x2 = rnd.next(x1 + 1, 1000);
                int y2 = rnd.next(y1 + 1, 1000);
                targets.push_back(rectangleTarget(x1, y1, x2, y2));
            } else {
                targets.push_back(circleTarget(rnd.next(-1000, 1000),
                                               rnd.next(-1000, 1000),
                                               rnd.next(1, 1000)));
            }
        }
        for (int i = 0; i < rnd.next(8, 25); ++i) {
            addShot(shots, rnd.next(-1000, 1000), rnd.next(-1000, 1000));
        }
    }

    int desiredShots = rnd.next(6, 14);
    while ((int)shots.size() < desiredShots) {
        const Target& target = rnd.any(targets);
        if (target.kind == "rectangle") {
            addShot(shots, rnd.next(target.a, target.c), rnd.next(target.b, target.d));
        } else {
            int dx = rnd.next(-target.c, target.c);
            int maxDy = 0;
            while ((long long)dx * dx + (long long)maxDy * maxDy <=
                   (long long)target.c * target.c) {
                ++maxDy;
            }
            --maxDy;
            addShot(shots, target.a + dx, target.b + rnd.next(-maxDy, maxDy));
        }
    }

    shuffle(targets.begin(), targets.end());
    shuffle(shots.begin(), shots.end());
    if ((int)shots.size() > 100) shots.resize(100);

    println((int)targets.size());
    for (const Target& target : targets) {
        if (target.kind == "rectangle") {
            println(target.kind, target.a, target.b, target.c, target.d);
        } else {
            println(target.kind, target.a, target.b, target.c);
        }
    }

    println((int)shots.size());
    for (const auto& shot : shots) {
        println(shot.first, shot.second);
    }

    return 0;
}
