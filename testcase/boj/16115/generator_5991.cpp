#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Dir { int dx, dy; double a; };

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Build primitive directions with angles
    vector<Dir> dirs;
    for (int dx = -3; dx <= 3; dx++) {
        for (int dy = -3; dy <= 3; dy++) {
            if (dx == 0 && dy == 0) continue;
            if (std::gcd(abs(dx), abs(dy)) != 1) continue;
            double ang = atan2((double)dy, (double)dx);
            if (ang < 0) ang += 2 * acos(-1.0);
            dirs.push_back({dx, dy, ang});
        }
    }
    sort(dirs.begin(), dirs.end(), [](const Dir &A, const Dir &B){
        return A.a < B.a;
    });
    int D = dirs.size();
    // Sample N: sometimes small, sometimes medium
    int N;
    if (rnd.next(0,1) == 0) {
        N = rnd.next(3, min(D, 6));
    } else {
        N = rnd.next(max(3, min(7, D)), min(D, 12));
    }
    // Prepare for selecting directions
    vector<int> base(D);
    iota(base.begin(), base.end(), 0);
    vector<double> angs(D);
    for (int i = 0; i < D; i++) angs[i] = dirs[i].a;
    vector<int> sel;
    // Choose N directions so that max angular gap < PI
    double PI = acos(-1.0);
    while (true) {
        shuffle(base.begin(), base.end());
        sel.assign(base.begin(), base.begin() + N);
        sort(sel.begin(), sel.end(), [&](int i, int j){ return angs[i] < angs[j]; });
        double maxGap = 0;
        for (int i = 0; i + 1 < N; i++) {
            maxGap = max(maxGap, angs[sel[i+1]] - angs[sel[i]]);
        }
        double wrap = angs[sel[0]] + 2*PI - angs[sel[N-1]];
        maxGap = max(maxGap, wrap);
        if (maxGap < PI - 1e-9) break;
    }
    // Radius hyper-parameter
    int Rmax = (rnd.next(0,1) == 0 ? rnd.next(5, 10) : rnd.next(11, 100));
    vector<int> rad(N);
    vector<pair<long long, long long>> P(N);
    // Generate radii & check no three consecutive collinear points
    auto gen_ok = [&]() {
        // Sample radii
        if (rnd.next(0,1) == 0) {
            for (int i = 0; i < N; i++) {
                rad[i] = rnd.next(1, Rmax);
            }
        } else {
            int tMax = rnd.next(1, min(N, 3));
            vector<int> ids(N);
            iota(ids.begin(), ids.end(), 0);
            shuffle(ids.begin(), ids.end());
            vector<bool> isMax(N, false);
            for (int i = 0; i < tMax; i++) isMax[ids[i]] = true;
            for (int i = 0; i < N; i++) {
                rad[i] = isMax[i] ? Rmax : rnd.next(1, Rmax - 1);
            }
        }
        // Build polygon points
        for (int i = 0; i < N; i++) {
            int d = sel[i];
            P[i].first  = 1LL * dirs[d].dx * rad[i];
            P[i].second = 1LL * dirs[d].dy * rad[i];
        }
        // Check no three consecutive collinear (including wrap)
        for (int i = 0; i < N; i++) {
            auto &A = P[i];
            auto &B = P[(i+1)%N];
            auto &C = P[(i+2)%N];
            long long x1 = B.first - A.first, y1 = B.second - A.second;
            long long x2 = C.first - B.first, y2 = C.second - B.second;
            if (x1 * y2 - y1 * x2 == 0) return false;
        }
        return true;
    };
    while (!gen_ok()) { }
    // Output the test case
    println(N);
    for (auto &pt : P) {
        println(pt.first, pt.second);
    }
    return 0;
}
