#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: occasionally generate a larger N for edge cases
    int N;
    if (rnd.next(0, 9) == 0) {
        N = rnd.next(50, 200);
    } else {
        N = rnd.next(1, 15);
    }
    // Number of points, up to twice N but capped at 20
    int C = rnd.next(1, min(20, N * 2));
    double p_dup = rnd.next();   // probability to duplicate a previous point
    double p_diag = rnd.next();  // probability to force X == Y
    vector<pair<int,int>> pts;
    pts.reserve(C);
    for (int i = 0; i < C; i++) {
        double r = rnd.next();
        if (i > 0 && r < p_dup) {
            // duplicate a random previous point
            int idx = rnd.next(0, (int)pts.size() - 1);
            pts.push_back(pts[idx]);
        } else if (rnd.next() < p_diag) {
            // diagonal point X == Y
            int d = rnd.next(1, N);
            pts.emplace_back(d, d);
        } else {
            // random point in [1, N]
            int x = rnd.next(1, N);
            int y = rnd.next(1, N);
            pts.emplace_back(x, y);
        }
    }
    // shuffle to add order variability
    shuffle(pts.begin(), pts.end());
    // output
    println(N, C);
    for (auto &pr : pts) {
        println(pr.first, pr.second);
    }
    return 0;
}
