#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Rect {
    int x, y, id;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and r
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int r = inf.readInt(1, 10000, "r");
    inf.readEoln();

    // Read the N rectangles
    vector<Rect> a;
    a.reserve(N);
    bool has_origin = false;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(0, 10000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 10000000, "y_i");
        inf.readEoln();
        if (x == 0 && y == 0) has_origin = true;
        a.push_back({x, y, i});
    }
    ensuref(has_origin, "There must be a square containing (0,0): found none with x=0 and y=0");

    // Read d
    int d = inf.readInt(1, 1000000, "d");
    inf.readEoln();

    // No more input
    inf.readEof();

    // Check that rectangles do not overlap or touch
    // Sort by x
    vector<Rect> b = a;
    sort(b.begin(), b.end(), [&](const Rect &A, const Rect &B) {
        return A.x < B.x;
    });

    // Active set: rectangles whose x + r >= current.x
    set<pair<int,int>> active; // (y, id)
    int left = 0;
    for (int right = 0; right < N; right++) {
        const Rect &cur = b[right];
        // Remove from active those too far left in x
        while (left < right && (long long)b[left].x + r < cur.x) {
            active.erase({b[left].y, b[left].id});
            left++;
        }
        // In active set, any rect has interval [x_i, x_i+r] that intersects/touches [cur.x, cur.x+r]
        // Now check y-interval overlap/touch: [y_i, y_i+r] and [cur.y, cur.y+r]
        int y_lo = cur.y - r;
        int y_hi = cur.y + r;
        auto it = active.lower_bound({y_lo, -1});
        while (it != active.end() && it->first <= y_hi) {
            int other_id = it->second;
            // locate other rectangle
            // We need its x,y
            const Rect &oth = a[other_id];
            // They overlap/touch both in x and y => forbidden
            ensuref(false,
                "Rectangles %d and %d overlap or touch: (%d,%d) vs (%d,%d)",
                cur.id, oth.id, cur.x, cur.y, oth.x, oth.y);
            ++it;
        }
        active.insert({cur.y, cur.id});
    }

    return 0;
}
