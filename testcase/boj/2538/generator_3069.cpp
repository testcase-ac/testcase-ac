#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Paper size
    int W = rnd.next(3, 10);
    int H = rnd.next(3, 10);

    // Decide whether to make one indent
    bool make_indent = rnd.next() < 0.7;
    int side = -1, a = 0, b = 0, d = 0;
    if (make_indent) {
        side = rnd.next(0, 3);
        if (side == 0 || side == 2) {
            // indent on bottom or top: horizontal span [a,b], depth d
            a = rnd.next(1, W - 2);
            b = rnd.next(a + 1, W - 1);
            d = rnd.next(1, H - 1);
        } else {
            // indent on right or left: vertical span [a,b], depth d
            a = rnd.next(1, H - 2);
            b = rnd.next(a + 1, H - 1);
            d = rnd.next(1, W - 1);
        }
    }

    vector<pair<int,int>> pts;
    pts.reserve(12);

    // Start at (0,0)
    pts.emplace_back(0, 0);
    // Side 0: (0,0) -> (W,0)
    if (make_indent && side == 0) {
        pts.emplace_back(a, 0);
        pts.emplace_back(a, d);
        pts.emplace_back(b, d);
        pts.emplace_back(b, 0);
    }
    pts.emplace_back(W, 0);
    // Side 1: (W,0) -> (W,H)
    if (make_indent && side == 1) {
        pts.emplace_back(W, a);
        pts.emplace_back(W - d, a);
        pts.emplace_back(W - d, b);
        pts.emplace_back(W, b);
    }
    pts.emplace_back(W, H);
    // Side 2: (W,H) -> (0,H)
    if (make_indent && side == 2) {
        pts.emplace_back(b, H);
        pts.emplace_back(b, H - d);
        pts.emplace_back(a, H - d);
        pts.emplace_back(a, H);
    }
    pts.emplace_back(0, H);
    // Side 3: (0,H) -> (0,0)
    if (make_indent && side == 3) {
        pts.emplace_back(0, b);
        pts.emplace_back(d, b);
        pts.emplace_back(d, a);
        pts.emplace_back(0, a);
    }
    // Done, no need to repeat (0,0)

    // Output
    println(W, H);
    println((int)pts.size());
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
