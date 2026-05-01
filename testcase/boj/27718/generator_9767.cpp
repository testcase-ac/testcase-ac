#include "testlib.h"
using namespace std;

struct Seg {
    long long x1, y1, x2, y2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Seg> segs;

    int scenario = rnd.next(1, 6); // choose template scenario

    if (scenario == 1) {
        // Scenario 1: collinear chain like sample 2 (diagonal line)
        segs.push_back({0, 0, 1, 1});
        segs.push_back({1, 1, 2, 2});
        segs.push_back({2, 2, 3, 3});
        segs.push_back({0, 0, 2, 2});
        segs.push_back({1, 1, 3, 3});
        segs.push_back({0, 0, 3, 3});
    } else if (scenario == 2) {
        // Scenario 2: crossings and horizontals like sample 1
        segs.push_back({-2, -1, 0, 2});
        segs.push_back({0, 2, 2, -1});
        segs.push_back({-2, -1, 2, -1});
        segs.push_back({-2, 0, 2, 0});
    } else if (scenario == 3) {
        // Scenario 3: mixed horizontals, verticals, diagonals, overlaps at origin
        segs.push_back({-5, 0, 5, 0});    // big horizontal
        segs.push_back({0, -5, 0, 5});    // big vertical
        segs.push_back({-5, -5, 5, 5});   // main diagonal
        segs.push_back({-5, 5, 5, -5});   // other diagonal
        segs.push_back({0, 0, 5, 0});     // subsegment of horizontal
        segs.push_back({-2, 0, 2, 0});    // another subsegment
        segs.push_back({-5, 1, 5, 1});    // parallel horizontal
        segs.push_back({0, -2, 0, 2});    // subsegment vertical
    } else if (scenario == 4) {
        // Scenario 4: verticals – collinear, touching, disjoint parallels
        segs.push_back({10, -5, 10, 5});   // main vertical
        segs.push_back({10, -3, 10, -1});  // inside main
        segs.push_back({10, 5, 10, 8});    // touching at endpoint
        segs.push_back({12, -5, 12, 5});   // parallel, overlapping
        segs.push_back({12, 5, 12, 8});    // touching this parallel
        segs.push_back({14, -5, 14, -1});  // separate vertical
    } else if (scenario == 5) {
        // Scenario 5: random small general segments
        int M = rnd.next(1, 9);
        for (int i = 0; i < M; ++i) {
            long long x1 = rnd.next(-10, 10);
            long long y1 = rnd.next(-10, 10);
            long long x2, y2;
            do {
                x2 = rnd.next(-10, 10);
                y2 = rnd.next(-10, 10);
            } while (x1 == x2 && y1 == y2); // avoid zero-length
            segs.push_back({x1, y1, x2, y2});
        }
    } else { // scenario == 6
        // Scenario 6: many collinear segments on same line (horizontal/vertical/diagonal)
        int type = rnd.next(0, 2); // 0: horizontal y=0, 1: vertical x=0, 2: diagonal y=x
        int M = rnd.next(3, 10);
        for (int i = 0; i < M; ++i) {
            int a = rnd.next(-10, 10);
            int b;
            do {
                b = rnd.next(-10, 10);
            } while (a == b);
            if (type == 0) { // horizontal
                segs.push_back({a, 0, b, 0});
            } else if (type == 1) { // vertical
                segs.push_back({0, a, 0, b});
            } else { // diagonal y = x
                segs.push_back({a, a, b, b});
            }
        }
    }

    // Optional affine transform (scale + translate), staying comfortably in bounds
    int mode = rnd.next(0, 2); // 0: none, 1: small, 2: larger scale
    long long s = 1;
    long long dx = 0, dy = 0;

    if (mode == 0) {
        s = 1;
        dx = dy = 0;
    } else {
        vector<long long> scales = {1, 1, 1, 2, 5, 10, 100, 1000, 1000000};
        s = rnd.any(scales);
        // Base coordinates are within [-20, 20], so this keeps us well inside [-1e9, 1e9]
        dx = rnd.next(-100000000, 100000000);
        dy = rnd.next(-100000000, 100000000);
    }

    for (auto &sg : segs) {
        sg.x1 = sg.x1 * s + dx;
        sg.y1 = sg.y1 * s + dy;
        sg.x2 = sg.x2 * s + dx;
        sg.y2 = sg.y2 * s + dy;
    }

    // Randomly swap endpoints for variability
    for (auto &sg : segs) {
        if (rnd.next(0, 1)) {
            swap(sg.x1, sg.x2);
            swap(sg.y1, sg.y2);
        }
    }

    // Shuffle segment order
    shuffle(segs.begin(), segs.end());

    int N = (int)segs.size();

    println(N);
    for (const auto &sg : segs) {
        println(sg.x1, sg.y1, sg.x2, sg.y2);
    }

    return 0;
}
