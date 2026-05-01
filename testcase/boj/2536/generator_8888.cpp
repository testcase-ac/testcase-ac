#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Bus {
    int id;
    int x1, y1, x2, y2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose pattern type for variability
    int pattern = rnd.next(1, 4);

    // Grid size (keep small but varied, at least 2x2)
    int m, n;
    if (pattern == 1) {
        m = rnd.next(2, 8);
        n = rnd.next(2, 8);
    } else if (pattern == 2) {
        m = rnd.next(5, 15);
        n = rnd.next(5, 15);
    } else {
        m = rnd.next(5, 20);
        n = rnd.next(5, 20);
    }

    // Decide length of main path (number of buses in guaranteed path)
    int segCnt;
    if (pattern == 1) segCnt = rnd.next(1, 2);
    else if (pattern == 2) segCnt = rnd.next(2, 4);
    else segCnt = rnd.next(2, 5);

    vector<pair<int,int>> pts(segCnt + 1); // P0=S, Pseg=D

    vector<int> orient(segCnt); // 0 = horizontal, 1 = vertical

    // Generate a path ensuring S != D
    while (true) {
        // Start point S
        pts[0].first  = rnd.next(1, m);
        pts[0].second = rnd.next(1, n);

        // Orientations depending on pattern
        if (pattern == 1) {
            for (int i = 0; i < segCnt; ++i)
                orient[i] = rnd.next(0, 1);
        } else if (pattern == 2) {
            int allOri = rnd.next(0, 1); // all horizontal or all vertical
            for (int i = 0; i < segCnt; ++i)
                orient[i] = allOri;
        } else { // pattern 3 or 4-like
            orient[0] = rnd.next(0, 1);
            for (int i = 1; i < segCnt; ++i) {
                if (pattern == 3) {
                    // Prefer alternating
                    if (rnd.next(0, 3) == 0) orient[i] = orient[i - 1];
                    else orient[i] = 1 - orient[i - 1];
                } else {
                    // Prefer same orientation to create overlaps
                    if (rnd.next(0, 3) <= 1) orient[i] = orient[i - 1];
                    else orient[i] = 1 - orient[i - 1];
                }
            }
        }

        // Build successive points
        for (int i = 0; i < segCnt; ++i) {
            int x = pts[i].first;
            int y = pts[i].second;
            if (orient[i] == 0) { // horizontal: change x
                int nx;
                do {
                    nx = rnd.next(1, m);
                } while (nx == x);
                pts[i + 1] = make_pair(nx, y);
            } else { // vertical: change y
                int ny;
                do {
                    ny = rnd.next(1, n);
                } while (ny == y);
                pts[i + 1] = make_pair(x, ny);
            }
        }

        if (pts[0] != pts[segCnt])
            break; // ensure S != D
    }

    pair<int,int> S = pts[0];
    pair<int,int> D = pts[segCnt];

    vector<Bus> buses;
    buses.reserve(25);
    set<tuple<int,int,int,int>> used;

    auto addBus = [&](int x1, int y1, int x2, int y2) -> bool {
        // Ensure horizontal or vertical, and canonical ordering for dedup
        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
        } else {
            if (x1 > x2) swap(x1, x2);
        }
        tuple<int,int,int,int> key = make_tuple(x1, y1, x2, y2);
        if (used.count(key)) return false;
        used.insert(key);
        Bus b;
        b.id = -1;
        b.x1 = x1; b.y1 = y1; b.x2 = x2; b.y2 = y2;
        buses.push_back(b);
        return true;
    };

    // Main path buses: each connects pts[i] to pts[i+1], possibly extended
    for (int i = 0; i < segCnt; ++i) {
        int x1 = pts[i].first;
        int y1 = pts[i].second;
        int x2 = pts[i + 1].first;
        int y2 = pts[i + 1].second;

        if (y1 == y2) { // horizontal
            int y = y1;
            int minX = min(x1, x2);
            int maxX = max(x1, x2);

            int leftExt  = (minX > 1) ? rnd.next(0, minX - 1) : 0;
            int rightExt = (maxX < m) ? rnd.next(0, m - maxX) : 0;

            int lo = minX - leftExt;
            int hi = maxX + rightExt;
            if (lo == hi) { // safeguard, though shouldn't happen with m>=2 and x1!=x2
                if (lo > 1) --lo;
                else if (hi < m) ++hi;
            }
            addBus(lo, y, hi, y);
        } else { // vertical
            int x = x1;
            int minY = min(y1, y2);
            int maxY = max(y1, y2);

            int downExt = (minY > 1) ? rnd.next(0, minY - 1) : 0;
            int upExt   = (maxY < n) ? rnd.next(0, n - maxY) : 0;

            int lo = minY - downExt;
            int hi = maxY + upExt;
            if (lo == hi) { // safeguard
                if (lo > 1) --lo;
                else if (hi < n) ++hi;
            }
            addBus(x, lo, x, hi);
        }
    }

    int mainCount = (int)buses.size();

    // Try to add a direct S-D bus (shortcut) sometimes
    if (rnd.next(0, 3) == 0) {
        if (S.first == D.first) { // same column -> vertical bus
            int x = S.first;
            int minY = min(S.second, D.second);
            int maxY = max(S.second, D.second);
            int downExt = (minY > 1) ? rnd.next(0, minY - 1) : 0;
            int upExt   = (maxY < n) ? rnd.next(0, n - maxY) : 0;
            int lo = minY - downExt;
            int hi = maxY + upExt;
            if (lo == hi) {
                if (lo > 1) --lo;
                else if (hi < n) ++hi;
            }
            addBus(x, lo, x, hi);
        } else if (S.second == D.second) { // same row -> horizontal bus
            int y = S.second;
            int minX = min(S.first, D.first);
            int maxX = max(S.first, D.first);
            int leftExt  = (minX > 1) ? rnd.next(0, minX - 1) : 0;
            int rightExt = (maxX < m) ? rnd.next(0, m - maxX) : 0;
            int lo = minX - leftExt;
            int hi = maxX + rightExt;
            if (lo == hi) {
                if (lo > 1) --lo;
                else if (hi < m) ++hi;
            }
            addBus(lo, y, hi, y);
        }
    }

    // Extra random buses
    int maxTotal;
    if (pattern == 1) maxTotal = 8;
    else if (pattern == 2) maxTotal = 12;
    else maxTotal = 18;

    int extraMax = maxTotal - (int)buses.size();
    if (extraMax < 0) extraMax = 0;
    int extra = (extraMax == 0 ? 0 : rnd.next(0, extraMax));

    for (int i = 0; i < extra; ) {
        bool makeConnected = (rnd.next(0, 1) == 0); // half connected to some main point

        if (makeConnected) {
            // Pick a random point along the main path
            auto P = rnd.any(pts);
            int x = P.first;
            int y = P.second;
            int ori = rnd.next(0, 1);

            if (ori == 0) { // horizontal through (x,y)
                int left = rnd.next(1, x);
                int right = rnd.next(x, m);
                if (left == right) {
                    if (left > 1) --left;
                    else if (right < m) ++right;
                }
                if (addBus(left, y, right, y)) ++i;
            } else { // vertical through (x,y)
                int down = rnd.next(1, y);
                int up   = rnd.next(y, n);
                if (down == up) {
                    if (down > 1) --down;
                    else if (up < n) ++up;
                }
                if (addBus(x, down, x, up)) ++i;
            }
        } else {
            // Completely random bus
            int ori = rnd.next(0, 1);
            if (ori == 0) { // horizontal
                int y = rnd.next(1, n);
                int x1 = rnd.next(1, m);
                int x2;
                do {
                    x2 = rnd.next(1, m);
                } while (x2 == x1);
                if (addBus(x1, y, x2, y)) ++i;
            } else { // vertical
                int x = rnd.next(1, m);
                int y1 = rnd.next(1, n);
                int y2;
                do {
                    y2 = rnd.next(1, n);
                } while (y2 == y1);
                if (addBus(x, y1, x, y2)) ++i;
            }
        }
    }

    int k = (int)buses.size();

    // Assign bus IDs 1..k, but shuffle their association for variability
    vector<int> ids(k);
    iota(ids.begin(), ids.end(), 1);
    shuffle(ids.begin(), ids.end());
    for (int i = 0; i < k; ++i)
        buses[i].id = ids[i];

    // Shuffle output order of buses as well
    shuffle(buses.begin(), buses.end());

    // Output
    println(m, n);
    println(k);
    for (const auto &b : buses) {
        println(b.id, b.x1, b.y1, b.x2, b.y2);
    }
    println(S.first, S.second, D.first, D.second);

    return 0;
}
