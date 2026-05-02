#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    long long x;
    int type; // +1 entering, -1 leaving
    long long y1, y2;
    bool operator<(Event const& other) const {
        if (x != other.x) return x < other.x;
        return type > other.type; // add (+1) before remove (-1) at same x (not strictly needed for area)
    }
};

// Segment structure for coverage computation
struct Segment {
    long long y1, y2;
    int type; // +1 or -1
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<Event> events;
    events.reserve(2LL * N);

    for (int i = 0; i < N; ++i) {
        long long x1 = inf.readLong(0LL, 1000000000LL, "x1");
        inf.readSpace();
        long long x2 = inf.readLong(0LL, 1000000000LL, "x2");
        inf.readSpace();
        long long y1 = inf.readLong(0LL, 1000000000LL, "y1");
        inf.readSpace();
        long long y2 = inf.readLong(0LL, 1000000000LL, "y2");
        inf.readEoln();

        ensuref(x1 < x2, "Rectangle %d has non-positive width: x1=%lld, x2=%lld", i + 1, x1, x2);
        ensuref(y1 < y2, "Rectangle %d has non-positive height: y1=%lld, y2=%lld", i + 1, y1, y2);

        events.push_back({x1, +1, y1, y2});
        events.push_back({x2, -1, y1, y2});
    }

    // Check union area fits in 64-bit signed integer and is non-negative by computing it.
    sort(events.begin(), events.end());

    auto compute_covered_y = [](const vector<Segment>& segs) -> long long {
        if (segs.empty()) return 0LL;
        // sort by y1, and for ties process type (+1 before -1) to handle zero-length intervals safely
        vector<Segment> s = segs;
        sort(s.begin(), s.end(), [](const Segment& a, const Segment& b){
            if (a.y1 != b.y1) return a.y1 < b.y1;
            return a.type > b.type;
        });

        long long covered = 0;
        long long curStart = 0;
        int balance = 0;
        long long lastY = 0;

        bool first = true;
        for (const auto& seg : s) {
            long long y1 = seg.y1;
            long long y2 = seg.y2;
            int t = seg.type;

            if (first) {
                // initialize
                first = false;
                balance = 0;
                lastY = y1;
            }

            // when we move from lastY to y1, if balance>0, that segment is covered
            if (y1 > lastY && balance > 0) {
                covered += (y1 - lastY);
            }
            lastY = y1;

            // apply event at y1
            balance += t;
            ensuref(balance >= 0, "Internal error during coverage sweep: negative balance");
            // For axis-aligned rectangles with +1 at y1 and -1 at y2, balance should never be negative.

            // balance change doesn't directly add area; area added when moving to next distinct y
            // y2 is not explicitly used in this compressed representation; we instead store separate
            // events at y1 and y2. But here we are using segments (y1,y2) with +1/-1,
            // so we need to push events at y1 and y2.
        }

        // The above logic is incorrect for (y1,y2) segments; instead implement classic union of intervals.

        // Re-implement properly:

        covered = 0;
        if (s.empty()) return 0LL;
        long long cur_l = s[0].y1;
        long long cur_r = s[0].y2;
        for (size_t i = 1; i < s.size(); ++i) {
            long long a = s[i].y1;
            long long b = s[i].y2;
            if (b <= cur_l) {
                // completely before current, just extend union logic; since rectangles only add (+1/-1),
                // actually in this validator we only ever add positive intervals (no subtraction),
                // so we can assume type=+1 for all segments. Simplify: treat as list of intervals.
            }
        }
        // The above got messy; discard and implement simpler known-correct algorithm for union of intervals.

        return 0LL; // placeholder, but we'll not use this lambda anymore
    };

    // Rebuild: since rectangles always add area, we can compute union of intervals without type (+1/-1).
    // For each vertical slab between consecutive x, we have a multiset of intervals; but to validate
    // "answer always exists" and fit in 64-bit, it's enough to compute union using active intervals only.
    // We'll maintain active intervals as a vector of [y1,y2) intervals and recompute their union when x changes.
    long long lastX = events[0].x;
    __int128 totalArea = 0;

    vector<pair<long long,long long>> active; // intervals [y1,y2)

    auto union_y_length = [&](vector<pair<long long,long long>>& v) -> long long {
        if (v.empty()) return 0LL;
        sort(v.begin(), v.end());
        long long res = 0;
        long long curL = v[0].first;
        long long curR = v[0].second;
        for (size_t i = 1; i < v.size(); ++i) {
            long long a = v[i].first;
            long long b = v[i].second;
            if (a <= curR) {
                if (b > curR) curR = b;
            } else {
                res += (curR - curL);
                curL = a;
                curR = b;
            }
        }
        res += (curR - curL);
        return res;
    };

    size_t i = 0;
    const size_t E = events.size();
    while (i < E) {
        long long x = events[i].x;
        long long dx = x - lastX;
        if (dx < 0)
            ensuref(false, "Events are not sorted properly by x");
        if (dx > 0 && !active.empty()) {
            long long covY = union_y_length(active);
            totalArea += (__int128)covY * (__int128)dx;
            ensuref(totalArea >= 0, "Computed area became negative (overflow or logic error)");
            ensuref(totalArea <= (__int128)9223372036854775807LL,
                    "Total union area exceeds 64-bit signed range: %lld",
                    (long long)totalArea);
        }
        // process all events at this x
        while (i < E && events[i].x == x) {
            if (events[i].type == +1) {
                active.emplace_back(events[i].y1, events[i].y2);
            } else {
                // remove one instance of [y1,y2)
                bool found = false;
                for (size_t k = 0; k < active.size(); ++k) {
                    if (active[k].first == events[i].y1 && active[k].second == events[i].y2) {
                        active[k] = active.back();
                        active.pop_back();
                        found = true;
                        break;
                    }
                }
                ensuref(found, "Trying to remove non-existing interval at x=%lld, y=[%lld,%lld]",
                        events[i].x, events[i].y1, events[i].y2);
            }
            ++i;
        }
        lastX = x;
    }

    // No extra content
    inf.readEof();
}
