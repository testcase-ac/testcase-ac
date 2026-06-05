#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static void addSegment(vector<pair<int, int>>& segments, int l, int r) {
    if (l > r) swap(l, r);
    if (l == 0 && r == 0) r = 1;
    segments.push_back({l, r});
}

static void addDecoys(vector<pair<int, int>>& segments, int m, int count) {
    for (int i = 0; i < count; ++i) {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            int r = rnd.next(-50000, min(50000, m));
            int l = rnd.next(-50000, r);
            addSegment(segments, l, r);
        } else if (kind == 1) {
            int l = rnd.next(0, min(50000, m));
            int r = rnd.next(l, min(50000, m));
            addSegment(segments, l, r);
        } else if (kind == 2) {
            int l = rnd.next(max(-50000, m - 20), 50000);
            int r = rnd.next(l, 50000);
            addSegment(segments, l, r);
        } else {
            int l = rnd.next(-10, min(10, m));
            int r = rnd.next(l, min(50000, m + 20));
            addSegment(segments, l, r);
        }
    }
}

static void buildCoverable(vector<pair<int, int>>& segments, int m) {
    int x = 0;
    while (x < m) {
        int l = rnd.next(max(-50000, x - rnd.next(0, 5)), x);
        int r = rnd.next(x + 1, min(50000, x + rnd.next(1, 12)));
        addSegment(segments, l, r);
        x = r;
    }

    addDecoys(segments, m, rnd.next(3, 12));
}

static void buildImpossibleGap(vector<pair<int, int>>& segments, int m) {
    int gap = rnd.next(0, m - 1);
    int leftLimit = gap;
    int rightStart = gap + 1;

    for (int i = 0; i < rnd.next(2, 8); ++i) {
        int r = rnd.next(0, leftLimit);
        int l = rnd.next(-50000, r);
        addSegment(segments, l, r);
    }
    for (int i = 0; i < rnd.next(2, 8); ++i) {
        int l = rnd.next(rightStart, min(50000, max(rightStart, m)));
        int r = rnd.next(l, min(50000, m + rnd.next(0, 15)));
        addSegment(segments, l, r);
    }
    addDecoys(segments, m, rnd.next(1, 6));
}

static void buildNested(vector<pair<int, int>>& segments, int m) {
    addSegment(segments, -rnd.next(0, 20), m);
    addSegment(segments, 0, rnd.next(1, m));
    addSegment(segments, rnd.next(0, m - 1), m);

    int center = rnd.next(0, m);
    for (int i = 0; i < rnd.next(4, 14); ++i) {
        int l = rnd.next(max(-50000, center - 20), center);
        int r = rnd.next(center, min(50000, center + 20));
        addSegment(segments, l, r);
    }
}

static void buildBounds(vector<pair<int, int>>& segments, int m) {
    addSegment(segments, -50000, 0);
    addSegment(segments, 0, rnd.next(1, m));
    addSegment(segments, rnd.next(0, m), 50000);
    addSegment(segments, -50000, 50000);
    addDecoys(segments, m, rnd.next(5, 15));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int m = mode == 3 ? 50000 : rnd.next(1, 60);

    vector<pair<int, int>> segments;
    if (mode == 0) {
        buildCoverable(segments, m);
    } else if (mode == 1) {
        buildImpossibleGap(segments, m);
    } else if (mode == 2) {
        buildNested(segments, m);
    } else {
        buildBounds(segments, m);
    }

    shuffle(segments.begin(), segments.end());

    println(m);
    for (auto [l, r] : segments) {
        println(l, r);
    }
    println(0, 0);
    return 0;
}
