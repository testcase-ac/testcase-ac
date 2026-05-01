#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: bias towards small, medium, large
    int tN = rnd.any(vector<int>{-2, 0, 2});
    int N = rnd.wnext(33, tN) + 3;  // N in [3,35]

    // Decide shape type: circle or ellipse
    bool ellipse = rnd.next(0, 1) == 0;

    // Base radius and axes
    int r_base = rnd.next(500, 3000);
    int a = r_base;
    int b = ellipse
            ? rnd.next(max(100, r_base - 500), r_base + 500)
            : r_base;

    int max_r = max(a, b);
    // Center so that polygon stays within [1,10000]
    int cx = rnd.next(max_r + 1, 10000 - max_r - 1);
    int cy = rnd.next(max_r + 1, 10000 - max_r - 1);

    const double PI = acos(-1.0);
    double offset = rnd.next() * 2 * PI;

    vector<pair<int,int>> pts;
    pts.reserve(N);
    for (int i = 0; i < N; i++) {
        double ang = offset + 2 * PI * i / N;
        double x = cx + a * cos(ang);
        double y = cy + b * sin(ang);
        int xi = int(round(x));
        int yi = int(round(y));
        pts.emplace_back(xi, yi);
    }
    // Currently in CCW order; reverse for clockwise
    reverse(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
