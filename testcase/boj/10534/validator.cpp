#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>
#include <limits>
using namespace std;

struct Entry {
    int y1, y2;
    int id;
};

struct Event {
    int x;
    bool isStart; // true = start, false = end
    int id;
    bool operator<(Event const &o) const {
        if (x != o.x) return x < o.x;
        // at same x, end (isStart=false) comes before start (isStart=true)
        return isStart < o.isStart;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    // Storage
    vector<int> xs(N), ys(N), ws(N), hs(N);
    vector<int> x1(N), x2(N), y1(N), y2(N);

    // Read rectangles
    for (int i = 0; i < N; i++) {
        // X, Y, W, H
        long long X = inf.readInt((long long)numeric_limits<int>::min(),
                                  (long long)numeric_limits<int>::max(),
                                  "X_i");
        inf.readSpace();
        long long Y = inf.readInt((long long)numeric_limits<int>::min(),
                                  (long long)numeric_limits<int>::max(),
                                  "Y_i");
        inf.readSpace();
        int W = inf.readInt(1, 500, "W_i");
        inf.readSpace();
        int H = inf.readInt(1, 500, "H_i");
        inf.readEoln();

        // Compute x2, y2 and ensure they fit in 32-bit signed
        long long xx2 = X + (long long)W;
        long long yy2 = Y + (long long)H;
        ensuref(xx2 <= numeric_limits<int>::max(),
                "X_i + W_i overflows 32-bit at rect %d: %lld + %d = %lld",
                i, X, W, xx2);
        ensuref(yy2 <= numeric_limits<int>::max(),
                "Y_i + H_i overflows 32-bit at rect %d: %lld + %d = %lld",
                i, Y, H, yy2);

        xs[i] = (int)X;
        ys[i] = (int)Y;
        ws[i] = W;
        hs[i] = H;
        x1[i] = (int)X;
        y1[i] = (int)Y;
        x2[i] = (int)xx2;
        y2[i] = (int)yy2;
    }

    // Build sweep events
    vector<Event> events;
    events.reserve(2 * N);
    for (int i = 0; i < N; i++) {
        events.push_back({ x1[i], true,  i });
        events.push_back({ x2[i], false, i });
    }
    sort(events.begin(), events.end());

    // Active set of intervals, sorted by y1, then by id
    struct Cmp {
        bool operator()(Entry const &a, Entry const &b) const {
            if (a.y1 != b.y1) return a.y1 < b.y1;
            return a.id < b.id;
        }
    };
    set<Entry, Cmp> active;

    // Sweep to detect any positive-area overlaps
    for (auto &e : events) {
        int id = e.id;
        int cy1 = y1[id];
        int cy2 = y2[id];
        if (e.isStart) {
            // Check for overlap with neighbors in active
            Entry probe{ cy1, cy2, id };
            auto it = active.lower_bound(probe);
            // Check the one with y1 >= cy1
            if (it != active.end()) {
                // positive y-overlap if it->y1 < cy2 and it->y2 > cy1
                if ((long long)it->y1 < (long long)cy2 && (long long)it->y2 > (long long)cy1) {
                    ensuref(false,
                            "Rectangles %d and %d overlap: [%d,%d]x[%d,%d] vs [%d,%d]x[%d,%d]",
                            id, it->id,
                            x1[id], x2[id], y1[id], y2[id],
                            x1[it->id], x2[it->id], y1[it->id], y2[it->id]);
                }
            }
            // Check the one immediately before
            if (it != active.begin()) {
                auto pit = prev(it);
                if ((long long)pit->y1 < (long long)cy2 && (long long)pit->y2 > (long long)cy1) {
                    ensuref(false,
                            "Rectangles %d and %d overlap: [%d,%d]x[%d,%d] vs [%d,%d]x[%d,%d]",
                            id, pit->id,
                            x1[id], x2[id], y1[id], y2[id],
                            x1[pit->id], x2[pit->id], y1[pit->id], y2[pit->id]);
                }
            }
            // Insert into active
            active.insert(probe);
        } else {
            // Remove from active
            Entry torem{ cy1, cy2, id };
            auto it = active.find(torem);
            ensuref(it != active.end(),
                    "Attempt to remove non-existent interval for rect %d", id);
            active.erase(it);
        }
    }

    inf.readEof();
    return 0;
}
