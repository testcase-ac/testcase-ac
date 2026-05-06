#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Seg {
    long long x1, y1, x2, y2;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long COORD_MIN = -1000000LL;
    const long long COORD_MAX =  1000000LL;
    const int N_MAX = 100000;

    int N = inf.readInt(0, N_MAX, "N");
    inf.readEoln();

    vector<Seg> segs;
    segs.reserve(N);

    auto sgn = [](long long x) -> int {
        if (x < 0) return -1;
        if (x > 0) return 1;
        return 0;
    };

    for (int i = 0; i < N; ++i) {
        long long x1 = inf.readLong(COORD_MIN, COORD_MAX, "x1");
        inf.readSpace();
        long long y1 = inf.readLong(COORD_MIN, COORD_MAX, "y1");
        inf.readSpace();
        long long x2 = inf.readLong(COORD_MIN, COORD_MAX, "x2");
        inf.readSpace();
        long long y2 = inf.readLong(COORD_MIN, COORD_MAX, "y2");
        inf.readEoln();

        ensuref(!(x1 == x2 && y1 == y2),
                "Segment %d is degenerate (same endpoints)", i);

        ensuref(x1 != x2, "Segment %d is vertical, which is forbidden", i);
        ensuref(y1 != y2, "Segment %d is horizontal, which is forbidden", i);

        // store
        segs.push_back({x1, y1, x2, y2});
    }

    long long x0 = inf.readLong(COORD_MIN, COORD_MAX, "x0");
    inf.readEoln();

    // Check segments don't intersect and endpoints don't coincide
    // Orientation and intersection helpers
    auto orient = [](long long ax, long long ay,
                     long long bx, long long by,
                     long long cx, long long cy) -> int {
        __int128 vx1 = (__int128)(bx - ax) * (cy - ay);
        __int128 vx2 = (__int128)(by - ay) * (cx - ax);
        __int128 v = vx1 - vx2;
        if (v < 0) return -1;
        if (v > 0) return 1;
        return 0;
    };

    auto onSegment = [](long long ax, long long ay,
                        long long bx, long long by,
                        long long cx, long long cy) -> bool {
        // c on closed segment ab, assuming collinear
        if (min(ax, bx) <= cx && cx <= max(ax, bx) &&
            min(ay, by) <= cy && cy <= max(ay, by))
            return true;
        return false;
    };

    auto segmentsProperlyIntersect = [&](const Seg& s1, const Seg& s2) -> bool {
        long long x1 = s1.x1, y1 = s1.y1, x2 = s1.x2, y2 = s1.y2;
        long long x3 = s2.x1, y3 = s2.y1, x4 = s2.x2, y4 = s2.y2;

        int o1 = orient(x1, y1, x2, y2, x3, y3);
        int o2 = orient(x1, y1, x2, y2, x4, y4);
        int o3 = orient(x3, y3, x4, y4, x1, y1);
        int o4 = orient(x3, y3, x4, y4, x2, y2);

        // General case
        if (o1 * o2 < 0 && o3 * o4 < 0) return true;

        // Collinear cases should not happen per statement
        if (o1 == 0 && onSegment(x1, y1, x2, y2, x3, y3)) return true;
        if (o2 == 0 && onSegment(x1, y1, x2, y2, x4, y4)) return true;
        if (o3 == 0 && onSegment(x3, y3, x4, y4, x1, y1)) return true;
        if (o4 == 0 && onSegment(x3, y3, x4, y4, x2, y2)) return true;

        return false;
    };

    // Check endpoints distinct
    {
        // sort by (x,y)
        vector<pair<long long,long long>> pts;
        pts.reserve(2 * N);
        for (int i = 0; i < N; ++i) {
            pts.emplace_back(segs[i].x1, segs[i].y1);
            pts.emplace_back(segs[i].x2, segs[i].y2);
        }
        sort(pts.begin(), pts.end());
        for (size_t i = 1; i < pts.size(); ++i) {
            ensuref(!(pts[i] == pts[i-1]),
                    "Two segment endpoints coincide at (%lld, %lld)",
                    pts[i].first, pts[i].second);
        }
    }

    // O(N^2) intersection check is too slow; use sweep line (Bentley–Ottmann style)
    struct Event {
        long long x;
        int type; // 0 = left, 1 = right
        int id;
        bool operator<(Event const& other) const {
            if (x != other.x) return x < other.x;
            // Process left endpoints before right endpoints at same x
            return type < other.type;
        }
    };

    vector<Event> events;
    events.reserve(2 * N);

    vector<double> atX0Y; // optional debugging; unused
    atX0Y.reserve(N);

    // Pre-normalize segments so that x1 < x2
    for (int i = 0; i < N; ++i) {
        if (segs[i].x2 < segs[i].x1) {
            swap(segs[i].x1, segs[i].x2);
            swap(segs[i].y1, segs[i].y2);
        }
        events.push_back({segs[i].x1, 0, i});
        events.push_back({segs[i].x2, 1, i});
    }
    sort(events.begin(), events.end());

    struct ActiveCmp {
        const vector<Seg>* pSegs;
        double xCur;
        bool operator()(int a, int b) const {
            if (a == b) return false;
            const Seg& sa = (*pSegs)[a];
            const Seg& sb = (*pSegs)[b];

            auto yAt = [&](const Seg& s) -> long double {
                long double x1 = s.x1, y1 = s.y1, x2 = s.x2, y2 = s.y2;
                if (x2 == x1) return min(y1, y2); // should not happen (no vertical)
                long double t = ((long double)xCur - x1) / (x2 - x1);
                return y1 + t * (y2 - y1);
            };

            long double ya = yAt(sa);
            long double yb = yAt(sb);
            if (ya != yb) return ya < yb;
            // tie-breaker to make strict weak ordering
            return a < b;
        }
    };

    ActiveCmp cmp;
    cmp.pSegs = &segs;
    cmp.xCur = 0.0L;

    set<int, ActiveCmp> active(cmp);

    auto checkNeighbor = [&](set<int, ActiveCmp>::iterator it1,
                             set<int, ActiveCmp>::iterator it2) {
        if (it1 == active.end() || it2 == active.end()) return;
        int id1 = *it1, id2 = *it2;
        if (id1 == id2) return;
        if (segmentsProperlyIntersect(segs[id1], segs[id2])) {
            ensuref(false,
                    "Segments %d and %d intersect, which is forbidden",
                    id1, id2);
        }
    };

    vector< set<int, ActiveCmp>::iterator > where(N);

    for (const auto& e : events) {
        cmp.xCur = e.x + 1e-9; // slightly inside the segment interval

        int id = e.id;
        if (e.type == 0) { // left endpoint -> insert
            auto it = active.insert(id).first;
            where[id] = it;

            if (it != active.begin()) {
                auto itPrev = it; --itPrev;
                checkNeighbor(itPrev, it);
            }
            auto itNext = it; ++itNext;
            if (itNext != active.end()) {
                checkNeighbor(it, itNext);
            }
        } else { // right endpoint -> erase
            auto it = where[id];
            if (it != active.begin()) {
                auto itPrev = it; --itPrev;
                auto itNext = it; ++itNext;
                if (itNext != active.end()) {
                    checkNeighbor(itPrev, itNext);
                }
            }
            active.erase(it);
        }
    }

    // Now also simulate the ball to ensure it always reaches some final x (i.e., falls to -infinity)
    // according to the model. This guards against impossible configurations like infinite loops.

    // Precompute for each segment its "downward" direction (from higher y to lower y)
    vector<long long> dx(N), dy(N);
    for (int i = 0; i < N; ++i) {
        long long x1 = segs[i].x1, y1 = segs[i].y1;
        long long x2 = segs[i].x2, y2 = segs[i].y2;
        if (y1 > y2) {
            dx[i] = x2 - x1;
            dy[i] = y2 - y1; // negative
        } else {
            dx[i] = x1 - x2;
            dy[i] = y1 - y2; // negative
        }
        // dy[i] must be < 0 since no horizontal
        ensuref(dy[i] < 0, "Internal error: dy not negative for segment %d", i);
    }

    auto verticalHit = [&](long long x, int curSeg) -> int {
        // find segment directly below point (x, current_y=+inf or endpoint y) with maximum y
        // We'll scan all segments; O(N^2) worst but just for validation, acceptable constraints ~1e5 is large.
        // To keep it safe, we instead only check that there is no cycle by limiting depth.
        // Here, just used by simulation; we will do naive O(N) scan per step and bound steps by N.
        long long bestId = -1;
        long double bestY = -1e100L;
        long double fromY = 1e100L;
        if (curSeg != -1) {
            // starting from endpoint of curSeg (lower endpoint)
            long long x1 = segs[curSeg].x1, y1 = segs[curSeg].y1;
            long long x2 = segs[curSeg].x2, y2 = segs[curSeg].y2;
            long long sx, sy;
            if (y1 < y2) { sx = x1; sy = y1; } else { sx = x2; sy = y2; }
            ensuref(sx == x, "Vertical hit x mismatch: expected %lld got %lld", sx, x);
            fromY = sy;
        }
        for (int i = 0; i < N; ++i) {
            long long X1 = segs[i].x1, Y1 = segs[i].y1;
            long long X2 = segs[i].x2, Y2 = segs[i].y2;
            if (!(min(X1, X2) <= x && x <= max(X1, X2))) continue;
            long double t = (long double)(x - X1) / (long double)(X2 - X1);
            long double y = (long double)Y1 + t * (long double)(Y2 - Y1);
            if (y < fromY && y > bestY) {
                bestY = y;
                bestId = i;
            }
        }
        return (int)bestId;
    };

    auto flowDown = [&](int curSeg) -> pair<long long,int> {
        // Move ball along curSeg in the "downward" direction until an endpoint;
        // then drop vertically.
        long long x1 = segs[curSeg].x1, y1 = segs[curSeg].y1;
        long long x2 = segs[curSeg].x2, y2 = segs[curSeg].y2;
        long long sx, sy;
        if (y1 < y2) { sx = x1; sy = y1; }
        else         { sx = x2; sy = y2; }
        int nxt = verticalHit(sx, curSeg);
        return make_pair(sx, nxt);
    };

    // Simulate with cycle guard
    {
        int steps = 0;
        int curSeg = verticalHit(x0, -1);
        long long curX = x0;
        while (curSeg != -1) {
            ensuref(steps <= N,
                    "Ball simulation exceeds N (%d) steps; possible loop in geometry", N);
            auto res = flowDown(curSeg);
            curX = res.first;
            curSeg = res.second;
            ++steps;
        }
        // curX is final x; within coordinate range by construction
        ensuref(COORD_MIN <= curX && curX <= COORD_MAX,
                "Final x-coordinate %lld out of allowed range", curX);
    }

    inf.readEof();
}
