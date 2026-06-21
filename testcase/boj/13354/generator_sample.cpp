#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Stroke {
    int x1;
    int y1;
    int x2;
    int y2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
    } else if (mode == 3) {
        n = rnd.next(1, 3);
        m = rnd.next(8, 18);
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(1, 3);
    } else {
        n = rnd.next(8, 20);
        m = rnd.next(8, 20);
    }

    int q = rnd.next(1, min(45, max(1, n + m + 12)));
    vector<Stroke> strokes;
    strokes.reserve(q);

    auto addHorizontal = [&]() {
        int x = rnd.next(1, n);
        int y1 = rnd.next(1, m);
        int y2 = rnd.next(y1, m);
        strokes.push_back({x, y1, x, y2});
    };

    auto addVertical = [&]() {
        int y = rnd.next(1, m);
        int x1 = rnd.next(1, n);
        int x2 = rnd.next(x1, n);
        strokes.push_back({x1, y, x2, y});
    };

    auto addPoint = [&]() {
        int x = rnd.next(1, n);
        int y = rnd.next(1, m);
        strokes.push_back({x, y, x, y});
    };

    auto addBoundary = [&]() {
        if (rnd.next(0, 1) == 0) {
            int x = rnd.any(vector<int>{1, n});
            strokes.push_back({x, 1, x, m});
        } else {
            int y = rnd.any(vector<int>{1, m});
            strokes.push_back({1, y, n, y});
        }
    };

    auto addCrossing = [&]() {
        if ((int)strokes.size() + 2 > q) {
            addPoint();
            return;
        }
        int x = rnd.next(1, n);
        int y = rnd.next(1, m);
        strokes.push_back({x, 1, x, m});
        strokes.push_back({1, y, n, y});
    };

    while ((int)strokes.size() < q) {
        int choice = rnd.next(0, 99);
        if (choice < 24) {
            addHorizontal();
        } else if (choice < 48) {
            addVertical();
        } else if (choice < 62) {
            addPoint();
        } else if (choice < 78) {
            addBoundary();
        } else if (choice < 90 && !strokes.empty()) {
            strokes.push_back(rnd.any(strokes));
        } else {
            addCrossing();
        }
    }

    if ((int)strokes.size() > q) {
        strokes.resize(q);
    }
    shuffle(strokes.begin(), strokes.end());

    println(n, m, q);
    for (const Stroke& stroke : strokes) {
        println(stroke.x1, stroke.y1, stroke.x2, stroke.y2);
    }

    return 0;
}
