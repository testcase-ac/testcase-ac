#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

vector<pair<double,double>> genPoints(int cnt, double scale) {
    vector<pair<double,double>> pts;
    int maxC = int(scale * 10 + 0.5);
    if (maxC < 0) maxC = 0;
    bool cluster = (cnt > 1) && rnd.next(0, 1);
    if (cluster) {
        int kc = rnd.next(1, min(cnt, 3));
        vector<pair<int,int>> centers(kc);
        for (int i = 0; i < kc; i++) {
            centers[i].first = rnd.next(-maxC, maxC);
            centers[i].second = rnd.next(-maxC, maxC);
        }
        int noise = max(1, maxC / 5);
        for (int i = 0; i < cnt; i++) {
            auto c = centers[rnd.next(0, kc - 1)];
            int dx = rnd.next(-noise, noise);
            int dy = rnd.next(-noise, noise);
            double x = (c.first + dx) / 10.0;
            double y = (c.second + dy) / 10.0;
            // clamp to [-scale, scale]
            x = max(-scale, min(scale, x));
            y = max(-scale, min(scale, y));
            pts.emplace_back(x, y);
        }
    } else {
        for (int i = 0; i < cnt; i++) {
            int xi = rnd.next(-maxC, maxC);
            int yi = rnd.next(-maxC, maxC);
            double x = xi / 10.0;
            double y = yi / 10.0;
            pts.emplace_back(x, y);
        }
    }
    return pts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of mice and holes
    int N = rnd.next(2, 10);
    int d = rnd.next(-3, 3);
    int M = max(1, min(10, N + d));

    // time and speed
    int S = rnd.next(1, 100);
    int V = rnd.next(1, 100);

    // prepare candidate scales and clamp to domain
    vector<double> scales = {
        0.5 * S * V,
        1.0 * S * V,
        2.0 * S * V,
        5.0 * S * V,
        1000.0
    };
    for (double &sc : scales) {
        if (sc > 1000.0) sc = 1000.0;
        if (sc < 0.0) sc = 0.0;
    }
    double scale = rnd.any(scales);

    // generate random points
    auto mice  = genPoints(N, scale);
    auto holes = genPoints(M, scale);

    // output
    println(N, M, S, V);
    for (auto &p : mice)
        printf("%.3f %.3f\n", p.first, p.second);
    for (auto &p : holes)
        printf("%.3f %.3f\n", p.first, p.second);

    return 0;
}
