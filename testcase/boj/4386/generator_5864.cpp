#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of stars
    int n = rnd.next(1, 12);
    println(n);

    // Choose generation pattern: 0 = uniform, 1 = clusters, 2 = collinear, 3 = circular
    int pattern = rnd.next(0, 3);

    if (pattern == 0) {
        // Uniform random points
        for (int i = 0; i < n; i++) {
            int xi = rnd.next(1, 100000);
            int yi = rnd.next(1, 100000);
            printf("%.2f %.2f\n", xi / 100.0, yi / 100.0);
        }
    }
    else if (pattern == 1) {
        // Clustered points
        int C = rnd.next(1, min(n, 5));
        vector<pair<int,int>> centers(C);
        for (int i = 0; i < C; i++) {
            centers[i].first  = rnd.next(1, 100000);
            centers[i].second = rnd.next(1, 100000);
        }
        int radius = rnd.wnext(5000, -1) + 1; // bias toward small cluster
        for (int i = 0; i < n; i++) {
            int ci = rnd.next(0, C - 1);
            int xi = centers[ci].first  + rnd.next(-radius, radius);
            int yi = centers[ci].second + rnd.next(-radius, radius);
            xi = max(1, min(100000, xi));
            yi = max(1, min(100000, yi));
            printf("%.2f %.2f\n", xi / 100.0, yi / 100.0);
        }
    }
    else if (pattern == 2) {
        // Collinear points along a random line segment
        pair<int,int> p1, p2;
        p1.first  = rnd.next(1, 100000);
        p1.second = rnd.next(1, 100000);
        do {
            p2.first  = rnd.next(1, 100000);
            p2.second = rnd.next(1, 100000);
        } while (p2 == p1);
        for (int i = 0; i < n; i++) {
            double t = rnd.next(); 
            double xf = p1.first * (1 - t) + p2.first * t;
            double yf = p1.second * (1 - t) + p2.second * t;
            int xi = int(xf + 0.5);
            int yi = int(yf + 0.5);
            xi = max(1, min(100000, xi));
            yi = max(1, min(100000, yi));
            printf("%.2f %.2f\n", xi / 100.0, yi / 100.0);
        }
    }
    else {
        // Circular arrangement with slight jitter
        const double PI = acos(-1.0);
        int radius = rnd.next(10000, 50000);
        int cx = rnd.next(radius, 100000 - radius);
        int cy = rnd.next(radius, 100000 - radius);
        for (int i = 0; i < n; i++) {
            double angle = rnd.next() * 2 * PI;
            double xf = cx + radius * cos(angle) + rnd.next(-1000, 1000) * 0.01;
            double yf = cy + radius * sin(angle) + rnd.next(-1000, 1000) * 0.01;
            int xi = int(xf + 0.5);
            int yi = int(yf + 0.5);
            xi = max(1, min(100000, xi));
            yi = max(1, min(100000, yi));
            printf("%.2f %.2f\n", xi / 100.0, yi / 100.0);
        }
    }

    return 0;
}
