#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of checkpoints
    int N = rnd.next(3, 30);
    // Choose a pattern type for diversity
    int type = rnd.next(0, 3);
    vector<pair<int,int>> pts(N);
    if (type == 0) {
        // Completely random points
        for (int i = 0; i < N; i++) {
            pts[i].first = rnd.next(-1000, 1000);
            pts[i].second = rnd.next(-1000, 1000);
        }
    } else if (type == 1) {
        // Horizontal line: y constant, x sorted
        vector<int> xs(N);
        for (int i = 0; i < N; i++) xs[i] = rnd.next(-1000, 1000);
        sort(xs.begin(), xs.end());
        int y0 = rnd.next(-1000, 1000);
        for (int i = 0; i < N; i++) pts[i] = { xs[i], y0 };
    } else if (type == 2) {
        // Vertical line: x constant, y sorted
        vector<int> ys(N);
        for (int i = 0; i < N; i++) ys[i] = rnd.next(-1000, 1000);
        sort(ys.begin(), ys.end());
        int x0 = rnd.next(-1000, 1000);
        for (int i = 0; i < N; i++) pts[i] = { x0, ys[i] };
    } else {
        // Random walk with small steps
        int x = rnd.next(-500, 500), y = rnd.next(-500, 500);
        pts[0] = { x, y };
        for (int i = 1; i < N; i++) {
            x += rnd.next(-20, 20);
            y += rnd.next(-20, 20);
            x = max(-1000, min(1000, x));
            y = max(-1000, min(1000, y));
            pts[i] = { x, y };
        }
    }
    // Introduce occasional duplicates to test edge handling
    for (int i = 1; i < N; i++) {
        if (rnd.next(0, 9) == 0) {
            pts[i] = pts[i-1];
        }
    }
    // Output the test case
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
