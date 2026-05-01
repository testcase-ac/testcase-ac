#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const double PI = acos(-1.0);
    // number of layers
    int L = rnd.next(1, 5);
    vector<pair<int,int>> pts;
    set<pair<int,int>> used;
    // radii for layers
    vector<double> radii(L);
    for (int i = 0; i < L; i++) {
        radii[i] = 20.0 + i * 15.0 + rnd.next(-5, 5);
    }
    // generate each layer on a rough circle
    for (int i = 0; i < L; i++) {
        int m = rnd.next(3, 6);
        vector<double> ang(m);
        for (int j = 0; j < m; j++) {
            ang[j] = rnd.next() * 2 * PI;
        }
        sort(ang.begin(), ang.end());
        for (int j = 0; j < m; j++) {
            double a = ang[j];
            double r = radii[i] + rnd.next(-2, 2);
            double x = r * cos(a);
            double y = r * sin(a);
            int xi = int(round(x));
            int yi = int(round(y));
            if (used.insert({xi, yi}).second) {
                pts.emplace_back(xi, yi);
            }
        }
        // optionally add one collinear point on an edge
        if (rnd.next(0, 1) == 0 && pts.size() >= 2) {
            // choose two last distinct points
            int sz = pts.size();
            auto p1 = pts[sz-1];
            auto p2 = pts[sz-2];
            int xi = (p1.first + p2.first) / 2;
            int yi = (p1.second + p2.second) / 2;
            if (used.insert({xi, yi}).second) {
                pts.emplace_back(xi, yi);
            }
        }
    }
    // extra random interior points (unused)
    int K = rnd.next(0, 5);
    for (int i = 0; i < K; i++) {
        double a = rnd.next() * 2 * PI;
        double r = rnd.next(1.0, max(1.0, radii[0] - 5.0));
        double x = r * cos(a);
        double y = r * sin(a);
        int xi = int(round(x));
        int yi = int(round(y));
        if (used.insert({xi, yi}).second) {
            pts.emplace_back(xi, yi);
        }
    }
    // shuffle points
    shuffle(pts.begin(), pts.end());
    // output
    int n = pts.size();
    println(n);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
