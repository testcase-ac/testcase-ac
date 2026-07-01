#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Fenwick {
    vector<int> bit;

    explicit Fenwick(int n) : bit(n + 1, 0) {}

    void add(int index, int value) {
        for (++index; index < static_cast<int>(bit.size()); index += index & -index) {
            bit[index] += value;
        }
    }

    int sumPrefix(int index) const {
        int result = 0;
        for (++index; index > 0; index -= index & -index) {
            result += bit[index];
        }
        return result;
    }

    int sumRange(int left, int right) const {
        if (left > right) {
            return 0;
        }
        return sumPrefix(right) - (left == 0 ? 0 : sumPrefix(left - 1));
    }
};

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct SideEvent {
    int x;
    int y1;
    int y2;
    int rectIndex;
    bool isLeft;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_N = 50000;
    constexpr int MAX_COORD = 1000000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<Rect> rectangles(n);
    vector<SideEvent> events;
    events.reserve(2 * n);

    for (int i = 0; i < n; ++i) {
        int x1 = inf.readInt(0, MAX_COORD, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, MAX_COORD, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, MAX_COORD, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, MAX_COORD, "y2");
        inf.readEoln();

        ensuref(x1 < x2, "rectangle %d must have x1 < x2: %d >= %d", i + 1, x1, x2);
        ensuref(y1 < y2, "rectangle %d must have y1 < y2: %d >= %d", i + 1, y1, y2);

        rectangles[i] = {x1, y1, x2, y2};
        events.push_back({x1, y1, y2, i, true});
        events.push_back({x2, y1, y2, i, false});
    }
    inf.readEof();

    sort(events.begin(), events.end(), [](const SideEvent& a, const SideEvent& b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        if (a.y1 != b.y1) {
            return a.y1 < b.y1;
        }
        if (a.y2 != b.y2) {
            return a.y2 < b.y2;
        }
        return a.rectIndex < b.rectIndex;
    });

    Fenwick activeY(MAX_COORD + 1);
    vector<char> active(n, false);

    for (int first = 0; first < static_cast<int>(events.size());) {
        int last = first;
        while (last < static_cast<int>(events.size()) && events[last].x == events[first].x) {
            ++last;
        }

        for (int i = first + 1; i < last; ++i) {
            ensuref(events[i - 1].y2 < events[i].y1,
                    "fences intersect or touch at x=%d between rectangles %d and %d",
                    events[first].x, events[i - 1].rectIndex + 1, events[i].rectIndex + 1);
        }

        for (int i = first; i < last; ++i) {
            const SideEvent& event = events[i];
            int intersections = activeY.sumRange(event.y1, event.y2);
            if (!event.isLeft && active[event.rectIndex]) {
                intersections -= 2;
            }
            ensuref(intersections == 0,
                    "fence of rectangle %d intersects or touches another fence at x=%d",
                    event.rectIndex + 1, event.x);
        }

        for (int i = first; i < last; ++i) {
            const SideEvent& event = events[i];
            if (!event.isLeft) {
                active[event.rectIndex] = false;
                activeY.add(event.y1, -1);
                activeY.add(event.y2, -1);
            }
        }

        for (int i = first; i < last; ++i) {
            const SideEvent& event = events[i];
            if (event.isLeft) {
                active[event.rectIndex] = true;
                activeY.add(event.y1, 1);
                activeY.add(event.y2, 1);
            }
        }

        first = last;
    }
}
