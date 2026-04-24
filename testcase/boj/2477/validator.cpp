#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Seg {
    long long x1, y1, x2, y2;
    bool horizontal;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(1, 20, "K");
    inf.readEoln();

    // Read 6 edges: direction and length
    vector<int> dir(6), len(6);
    for (int i = 0; i < 6; i++) {
        char buf[20];
        snprintf(buf, sizeof(buf), "dir[%d]", i);
        dir[i] = inf.readInt(1, 4, buf);
        inf.readSpace();
        snprintf(buf, sizeof(buf), "len[%d]", i);
        len[i] = inf.readInt(1, 500, buf);
        inf.readEoln();
    }

    // Check that horizontal and vertical displacements balance
    long long sum_east = 0, sum_west = 0, sum_south = 0, sum_north = 0;
    for (int i = 0; i < 6; i++) {
        if (dir[i] == 1) sum_east += len[i];
        else if (dir[i] == 2) sum_west += len[i];
        else if (dir[i] == 3) sum_south += len[i];
        else if (dir[i] == 4) sum_north += len[i];
    }
    ensuref(sum_east == sum_west,
            "Sum of East lengths (%lld) must equal sum of West lengths (%lld)",
            sum_east, sum_west);
    ensuref(sum_south == sum_north,
            "Sum of South lengths (%lld) must equal sum of North lengths (%lld)",
            sum_south, sum_north);

    // Ensure alternating axis: no two consecutive edges on same axis
    auto axis = [&](int d) {
        return (d == 1 || d == 2) ? 0 : 1;  // 0 = horizontal, 1 = vertical
    };
    for (int i = 0; i < 6; i++) {
        int j = (i + 1) % 6;
        ensuref(axis(dir[i]) != axis(dir[j]),
                "Edges %d and %d are on the same axis (dirs %d and %d)",
                i, j, dir[i], dir[j]);
    }

    // Build polygon vertices by walking from (0,0)
    vector<pair<long long,long long>> p(7);
    p[0] = {0LL, 0LL};
    for (int i = 0; i < 6; i++) {
        long long x = p[i].first;
        long long y = p[i].second;
        long long dx = 0, dy = 0;
        if (dir[i] == 1) dx = len[i];
        if (dir[i] == 2) dx = -len[i];
        if (dir[i] == 3) dy = -len[i];
        if (dir[i] == 4) dy = len[i];
        p[i+1] = {x + dx, y + dy};
    }
    // Check closure
    ensuref(p[6].first == 0 && p[6].second == 0,
            "Polygon does not close: end point is (%.0f, %.0f) instead of (0,0)",
            (double)p[6].first, (double)p[6].second);

    // Check turn types: exactly 5 left turns (convex), 1 right turn (reflex)
    int lefts = 0, rights = 0;
    for (int i = 0; i < 6; i++) {
        int j = (i + 1) % 6;
        // direction vectors for edges i and j
        long long dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
        if (dir[i] == 1) dx1 = 1;
        if (dir[i] == 2) dx1 = -1;
        if (dir[i] == 3) dy1 = -1;
        if (dir[i] == 4) dy1 = 1;
        if (dir[j] == 1) dx2 = 1;
        if (dir[j] == 2) dx2 = -1;
        if (dir[j] == 3) dy2 = -1;
        if (dir[j] == 4) dy2 = 1;
        long long cr = dx1 * dy2 - dy1 * dx2;
        ensuref(cr != 0,
                "Invalid turn (straight or 180°) at vertex %d: dirs %d to %d",
                i, dir[i], dir[j]);
        if (cr > 0) lefts++;
        else rights++;
    }
    ensuref(lefts == 5,
            "Expected 5 convex (left) turns, found %d", lefts);
    ensuref(rights == 1,
            "Expected 1 reflex (right) turn, found %d", rights);

    // Check for self-intersections (no intersections among non-adjacent edges)
    vector<Seg> seg(6);
    for (int i = 0; i < 6; i++) {
        auto a = p[i];
        auto b = p[i+1];
        if (a.first == b.first) {
            // vertical
            long long x = a.first;
            long long y1 = min(a.second, b.second);
            long long y2 = max(a.second, b.second);
            seg[i] = {x, y1, x, y2, false};
        } else {
            // horizontal
            long long y = a.second;
            long long x1 = min(a.first, b.first);
            long long x2 = max(a.first, b.first);
            seg[i] = {x1, y, x2, y, true};
        }
    }
    auto intersects = [&](const Seg &A, const Seg &B) {
        // overlapping or crossing or touching
        if (A.horizontal && B.horizontal) {
            if (A.y1 == B.y1 &&
                max(A.x1, B.x1) <= min(A.x2, B.x2))
                return true;
        } else if (!A.horizontal && !B.horizontal) {
            if (A.x1 == B.x1 &&
                max(A.y1, B.y1) <= min(A.y2, B.y2))
                return true;
        } else {
            const Seg &H = A.horizontal ? A : B;
            const Seg &V = A.horizontal ? B : A;
            if (V.x1 >= H.x1 && V.x1 <= H.x2 &&
                H.y1 >= V.y1 && H.y1 <= V.y2)
                return true;
        }
        return false;
    };
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            // skip adjacent edges
            if (j == (i + 1) % 6) continue;
            if (i == 0 && j == 5) continue;
            ensuref(!intersects(seg[i], seg[j]),
                    "Edges %d and %d intersect improperly", i, j);
        }
    }

    inf.readEof();
    return 0;
}
