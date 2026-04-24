#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// orientation of triplet (a,b,c): >0 if counter-clockwise, <0 if cw, 0 if collinear
ll orient(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c) {
    return (b.first - a.first) * (c.second - a.second)
         - (b.second - a.second) * (c.first - a.first);
}
// check if point c lies on segment ab (including endpoints)
bool onSegment(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c) {
    if (orient(a,b,c) != 0) return false;
    return c.first >= min(a.first,b.first)
        && c.first <= max(a.first,b.first)
        && c.second >= min(a.second,b.second)
        && c.second <= max(a.second,b.second);
}
// check if segments ab and cd intersect or touch
bool segmentsIntersect(const pair<ll,ll>& a, const pair<ll,ll>& b,
                       const pair<ll,ll>& c, const pair<ll,ll>& d) {
    ll o1 = orient(a,b,c);
    ll o2 = orient(a,b,d);
    ll o3 = orient(c,d,a);
    ll o4 = orient(c,d,b);
    // general case: proper intersection
    if ((o1 > 0 && o2 < 0 || o1 < 0 && o2 > 0)
     && (o3 > 0 && o4 < 0 || o3 < 0 && o4 > 0))
        return true;
    // special cases: collinear and overlapping
    if (o1 == 0 && onSegment(a,b,c)) return true;
    if (o2 == 0 && onSegment(a,b,d)) return true;
    if (o3 == 0 && onSegment(c,d,a)) return true;
    if (o4 == 0 && onSegment(c,d,b)) return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        int C = inf.readInt(3, 100, "C");
        inf.readEoln();

        vector<char> dirs(C);
        vector<int> steps(C);
        ll sum_abs = 0;

        for (int i = 0; i < C; i++) {
            string d = inf.readToken("x|y|z", "dir");
            dirs[i] = d[0];
            inf.readSpace();
            int s = inf.readInt(-1000, 1000, "step");
            ensuref(s != 0, "step[%d] is zero; must be non-zero", i);
            steps[i] = s;
            sum_abs += llabs((ll)s);
            inf.readEoln();
        }
        ensuref(sum_abs <= 1000, "total boundary length %lld exceeds 1000", sum_abs);

        // no two consecutive directions (by letter) can be the same, including last->first
        for (int i = 0; i < C; i++) {
            int ni = (i + 1) % C;
            ensuref(dirs[i] != dirs[ni],
                    "consecutive directions at segments %d and %d both '%c'", i, ni, dirs[i]);
        }

        // Build integer-based vertex coordinates in basis (e1, e2):
        // e1 = x axis, e2 = y axis, and z step is (e2 - e1).
        vector<pair<ll,ll>> ipt(C+1);
        ll p = 0, q = 0;
        ipt[0] = {0, 0};
        for (int i = 0; i < C; i++) {
            char d = dirs[i];
            int s = steps[i];
            if (d == 'x') {
                // move s * e1
                p += s;
            } else if (d == 'y') {
                // move s * e2
                q += s;
            } else {
                // 'z': move s * (e2 - e1)
                p -= s;
                q += s;
            }
            ipt[i+1] = {p, q};
        }
        // closure
        ensuref(ipt[C].first == 0 && ipt[C].second == 0,
                "polygon does not close; end vertex (%lld,%lld) != (0,0)",
                ipt[C].first, ipt[C].second);

        // no vertex repetition except start=end
        {
            set<pair<ll,ll>> seen;
            for (int i = 0; i < C; i++) {
                auto v = ipt[i];
                ensuref(!seen.count(v),
                        "self-touching at vertex %d: (%lld,%lld) repeated", i, v.first, v.second);
                seen.insert(v);
            }
        }

        // no self-intersection of non-adjacent edges
        // edges are (i)->(i+1) for i=0..C-1
        for (int i = 0; i < C; i++) {
            for (int j = i+1; j < C; j++) {
                // skip adjacent edges
                if (j == i+1) continue;
                // skip first and last adjacency
                if (i == 0 && j == C-1) continue;
                auto a = ipt[i];
                auto b = ipt[i+1];
                auto c = ipt[j];
                auto d = ipt[j+1];
                if (segmentsIntersect(a,b,c,d)) {
                    ensuref(false,
                            "edges (%d,%d) and (%d,%d) intersect or touch", i, i+1, j, j+1);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
