#include "testlib.h"
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(3, 10);
    int K = rnd.next(3, min(10, N));
    double eps = 1e-3;

    // Compute sector boundaries
    vector<double> bounds;
    for (int i = 0; i < K; i++) {
        bounds.push_back(i * (360.0 / K));
    }

    // Hyper-parameter: clustering vs uniform
    bool clusterMode = rnd.next() < 0.5;
    vector<double> centers;
    double width = (360.0 / K) * 0.8;
    double halfWidth = width / 2.0;
    if (clusterMode) {
        int C = rnd.next(1, min(N, 3));
        for (int i = 0; i < C; i++) {
            centers.push_back(rnd.next() * 360.0);
        }
    }

    // Generate angles avoiding boundaries
    vector<double> angles;
    for (int i = 0; i < N; i++) {
        double ang;
        bool ok;
        do {
            if (clusterMode && rnd.next() < 0.9) {
                int c = rnd.next(0, (int)centers.size() - 1);
                ang = fmod(centers[c] + (rnd.next() * 2 - 1) * halfWidth + 360.0, 360.0);
            } else {
                ang = rnd.next() * 360.0;
            }
            ok = true;
            for (double b : bounds) {
                double d = fmod(ang - b + 360.0, 360.0);
                if (d > 180.0) d = 360.0 - d;
                if (d < eps) { ok = false; break; }
            }
        } while (!ok);
        angles.push_back(ang);
    }

    // Output
    println(N, K);
    for (double a : angles) {
        printf("%.6f\n", a);
    }

    return 0;
}
