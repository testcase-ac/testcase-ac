#include "testlib.h"
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

Rect randomRect(int xl, int xr, int yl, int yr) {
    int x1 = rnd.next(xl, xr - 1);
    int x2 = rnd.next(x1 + 1, xr);
    int y1 = rnd.next(yl, yr - 1);
    int y2 = rnd.next(y1 + 1, yr);
    return {x1, y1, x2, y2};
}

Rect makeSameRect() {
    Rect r = randomRect(1, 40, 1, 40);
    return r;
}

pair<Rect, Rect> patternSameRect() {
    Rect r = makeSameRect();
    return {r, r};
}

pair<Rect, Rect> patternNoOverlap() {
    Rect r1 = randomRect(1, 15, 1, 15);
    Rect r2;
    int mode = rnd.next(0, 2); // 0: left-right, 1: up-down, 2: diagonal
    if (mode == 0) {
        r2 = randomRect(25, 40, 1, 15);
    } else if (mode == 1) {
        r2 = randomRect(1, 15, 25, 40);
    } else {
        r2 = randomRect(25, 40, 25, 40);
    }
    return {r1, r2};
}

pair<Rect, Rect> patternPartialSimple() {
    int x1 = rnd.next(5, 15);
    int x2 = rnd.next(x1 + 3, 25); // width at least 3
    int y1 = rnd.next(5, 15);
    int y2 = rnd.next(y1 + 3, 25); // height at least 3
    Rect r1 = {x1, y1, x2, y2};

    Rect r2;
    r2.x1 = rnd.next(r1.x1 + 1, r1.x2 - 2);
    r2.x2 = rnd.next(r1.x2 + 1, r1.x2 + 10);
    r2.y1 = rnd.next(max(1, r1.y1 - 10), r1.y1 - 1);
    r2.y2 = rnd.next(r1.y1 + 1, r1.y2 - 2);

    return {r1, r2};
}

pair<Rect, Rect> patternFirstInsideSecond() {
    Rect r1 = randomRect(10, 30, 10, 30);
    int ml = rnd.next(1, 5);
    int mr = rnd.next(1, 5);
    int mb = rnd.next(1, 5);
    int mt = rnd.next(1, 5);
    Rect r2;
    r2.x1 = max(1, r1.x1 - ml);
    r2.y1 = max(1, r1.y1 - mb);
    r2.x2 = r1.x2 + mr;
    r2.y2 = r1.y2 + mt;
    return {r1, r2};
}

pair<Rect, Rect> patternSecondInsideFirst() {
    int x1 = rnd.next(1, 20);
    int x2 = rnd.next(x1 + 4, 40); // width at least 4
    int y1 = rnd.next(1, 20);
    int y2 = rnd.next(y1 + 4, 40); // height at least 4
    Rect r1 = {x1, y1, x2, y2};

    Rect r2;
    r2.x1 = rnd.next(r1.x1 + 1, r1.x2 - 2);
    r2.x2 = rnd.next(r2.x1 + 1, r1.x2 - 1);
    r2.y1 = rnd.next(r1.y1 + 1, r1.y2 - 2);
    r2.y2 = rnd.next(r2.y1 + 1, r1.y2 - 1);

    return {r1, r2};
}

pair<Rect, Rect> patternEdgeTouchVertical() {
    Rect r1 = randomRect(1, 20, 1, 30);
    Rect r2;
    r2.x1 = r1.x2;
    r2.x2 = r2.x1 + rnd.next(1, 10);

    r2.y1 = rnd.next(max(1, r1.y1 - 5), r1.y2 - 1);
    int lowY2 = max(r1.y1 + 1, r2.y1 + 1);
    int highY2 = r1.y2 + 5;
    if (highY2 <= lowY2) highY2 = lowY2 + 1;
    r2.y2 = rnd.next(lowY2, highY2);

    return {r1, r2};
}

pair<Rect, Rect> patternEdgeTouchHorizontal() {
    Rect r1 = randomRect(1, 20, 1, 20);
    Rect r2;
    r2.y1 = r1.y2;
    r2.y2 = r2.y1 + rnd.next(1, 10);

    r2.x1 = rnd.next(max(1, r1.x1 - 5), r1.x2 - 1);
    int lowX2 = max(r1.x1 + 1, r2.x1 + 1);
    int highX2 = r1.x2 + 5;
    if (highX2 <= lowX2) highX2 = lowX2 + 1;
    r2.x2 = rnd.next(lowX2, highX2);

    return {r1, r2};
}

pair<Rect, Rect> patternCornerTouch() {
    Rect r1 = randomRect(1, 20, 1, 20);
    Rect r2;
    r2.x1 = r1.x2;
    r2.y1 = r1.y2;
    r2.x2 = r2.x1 + rnd.next(1, 10);
    r2.y2 = r2.y1 + rnd.next(1, 10);
    return {r1, r2};
}

pair<Rect, Rect> patternRandomGeneral() {
    Rect r1 = randomRect(1, 40, 1, 40);
    Rect r2 = randomRect(1, 40, 1, 40);
    return {r1, r2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 8);

    // Type indices:
    // 0: same rect (full cover)
    // 1: no overlap
    // 2: partial overlap
    // 3: first inside second
    // 4: second inside first
    // 5: edge touch vertical
    // 6: edge touch horizontal
    // 7: corner touch
    // 8: random general
    vector<int> types = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    shuffle(types.begin(), types.end());

    println(T);
    for (int i = 0; i < T; ++i) {
        int tp = types[i];
        pair<Rect, Rect> p;
        if (tp == 0) p = patternSameRect();
        else if (tp == 1) p = patternNoOverlap();
        else if (tp == 2) p = patternPartialSimple();
        else if (tp == 3) p = patternFirstInsideSecond();
        else if (tp == 4) p = patternSecondInsideFirst();
        else if (tp == 5) p = patternEdgeTouchVertical();
        else if (tp == 6) p = patternEdgeTouchHorizontal();
        else if (tp == 7) p = patternCornerTouch();
        else p = patternRandomGeneral();

        Rect a = p.first;
        Rect b = p.second;
        vector<int> vals = {a.x1, a.y1, a.x2, a.y2, b.x1, b.y1, b.x2, b.y2};
        println(vals);
    }

    return 0;
}
