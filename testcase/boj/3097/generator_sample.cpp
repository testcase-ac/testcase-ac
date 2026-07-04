#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Segment = pair<int, int>;

Segment randomSegment(int coordLimit) {
    return {rnd.next(-coordLimit, coordLimit), rnd.next(-coordLimit, coordLimit)};
}

void addClamped(vector<Segment>& segments, int x, int y) {
    segments.push_back({max(-1000, min(1000, x)), max(-1000, min(1000, y))});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 30);
    vector<Segment> segments;

    if (mode == 0) {
        int coordLimit = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            segments.push_back(randomSegment(coordLimit));
        }
    } else if (mode == 1) {
        int pairs = n / 2;
        int coordLimit = rnd.next(1, 200);
        for (int i = 0; i < pairs; ++i) {
            Segment s = randomSegment(coordLimit);
            segments.push_back(s);
            segments.push_back({-s.first, -s.second});
        }
        if ((int)segments.size() < n) {
            segments.push_back(randomSegment(10));
        }
        shuffle(segments.begin(), segments.end());
    } else if (mode == 2) {
        int sx = 0;
        int sy = 0;
        n = rnd.next(3, 12);
        for (int i = 0; i + 1 < n; ++i) {
            Segment s = randomSegment(80);
            segments.push_back(s);
            sx += s.first;
            sy += s.second;
        }
        addClamped(segments, -sx + rnd.next(-3, 3), -sy + rnd.next(-3, 3));
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        vector<int> values = {-1000, -999, -1, 0, 1, 999, 1000};
        for (int i = 0; i < n; ++i) {
            segments.push_back({rnd.any(values), rnd.any(values)});
        }
    } else {
        n = rnd.next(4, 20);
        Segment base = randomSegment(rnd.next(1, 300));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(3) == 0) {
                segments.push_back({-base.first, -base.second});
            } else if (rnd.next(2) == 0) {
                segments.push_back(base);
            } else {
                segments.push_back(randomSegment(30));
            }
        }
        shuffle(segments.begin(), segments.end());
    }

    println((int)segments.size());
    for (const Segment& segment : segments) {
        println(segment.first, segment.second);
    }

    return 0;
}
