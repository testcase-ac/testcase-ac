#include "testlib.h"

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

struct Segment {
    Point a;
    Point b;
};

string coord(int value, bool allowDecimal) {
    if (!allowDecimal || rnd.next(3) == 0) {
        return to_string(value);
    }

    int digits = rnd.next(1, 4);
    string s = to_string(abs(value)) + "." + string(digits, '0');
    if (value < 0) {
        s = "-" + s;
    }
    return s;
}

Segment makeHubSegment(Point hub, int radius, int mode) {
    if (mode == 0) {
        int dx = rnd.next(1, radius);
        return {{hub.x - dx, hub.y}, {hub.x + dx, hub.y}};
    }
    if (mode == 1) {
        int dy = rnd.next(1, radius);
        return {{hub.x, hub.y - dy}, {hub.x, hub.y + dy}};
    }

    int dx = rnd.next(1, radius);
    int dy = rnd.next(1, radius);
    if (rnd.next(2) == 0) {
        return {{hub.x - dx, hub.y - dy}, {hub.x + dx, hub.y + dy}};
    }
    return {{hub.x - dx, hub.y + dy}, {hub.x + dx, hub.y - dy}};
}

vector<Segment> makeGroup(int count, Point hub, int radius) {
    vector<Segment> segments;
    for (int i = 0; i < count; ++i) {
        segments.push_back(makeHubSegment(hub, radius, (i + rnd.next(3)) % 3));
    }
    shuffle(segments.begin(), segments.end());
    return segments;
}

void printSegment(const Segment& s, bool allowDecimal) {
    println(coord(s.a.x, allowDecimal), coord(s.a.y, allowDecimal), coord(s.b.x, allowDecimal),
            coord(s.b.y, allowDecimal));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(1, mode == 3 ? 18 : 8);
    int m = rnd.next(1, mode == 3 ? 18 : 8);

    int sinchonY = rnd.next(-3000, 3000);
    int anamY = rnd.next(-3000, 3000);
    int radius = rnd.next(mode == 0 ? 1 : 5, mode == 3 ? 900 : 120);

    Point sinchonHub{-rnd.next(2500, 8500), sinchonY};
    Point anamHub{rnd.next(2500, mode == 3 ? 20000 : 8500), anamY};

    if (mode == 1) {
        radius = rnd.next(1, 20);
        sinchonHub = {-1000 - radius, rnd.next(-50, 50)};
        anamHub = {1000 + radius, rnd.next(-50, 50)};
    } else if (mode == 2) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
        radius = rnd.next(20, 250);
        sinchonHub = {-rnd.next(3000, 9500), rnd.next(-9500, 9500)};
        anamHub = {rnd.next(3000, 45000), rnd.next(-45000, 45000)};
    }

    vector<Segment> sinchon = makeGroup(n, sinchonHub, radius);
    vector<Segment> anam = makeGroup(m, anamHub, radius);
    bool allowDecimal = rnd.next(2) == 0;

    println(n, m);
    for (const Segment& segment : sinchon) {
        printSegment(segment, allowDecimal);
    }
    for (const Segment& segment : anam) {
        printSegment(segment, allowDecimal);
    }

    return 0;
}
