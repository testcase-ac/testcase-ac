#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

double compute_volume(double a, double b, double h) {
    int m = 200; // even
    double d = h / m;
    double sum = 0;
    auto f2 = [&](double x) {
        double v = a * exp(-x*x) + b * sqrt(x);
        return v * v;
    };
    sum += f2(0) + f2(h);
    for (int i = 1; i < m; ++i) {
        double x = d * i;
        sum += f2(x) * (i % 2 == 0 ? 2 : 4);
    }
    double integral = sum * d / 3.0;
    return integral * acos(-1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 5);
    vector<double> a(N), b(N), h(N), v(N);
    const double delta = 1e-3;
    // generate bottles with distinct volumes
    while (true) {
        for (int i = 0; i < N; ++i) {
            a[i] = rnd.next(100, 1000) / 100.0; // [1.00,10.00]
            b[i] = rnd.next(100, 1000) / 100.0;
            h[i] = rnd.next(100, 1000) / 100.0;
            v[i] = compute_volume(a[i], b[i], h[i]);
        }
        bool ok = true;
        for (int i = 0; i < N && ok; ++i)
            for (int j = i+1; j < N; ++j)
                if (fabs(v[i] - v[j]) < delta) { ok = false; break; }
        if (ok) break;
    }
    // choose target volume V
    double V;
    if (N >= 2) {
        vector<pair<double,int>> vp;
        for (int i = 0; i < N; ++i) vp.emplace_back(v[i], i);
        sort(vp.begin(), vp.end());
        int idx = rnd.next(0, N-2);
        double v1 = vp[idx].first, v2 = vp[idx+1].first;
        V = (v1 + v2) / 2.0;
    } else {
        // N == 1
        double dv = rnd.next(1, 100) / 1000.0; // [0.001,0.1]
        if (rnd.next(0,1)) V = v[0] + dv;
        else V = v[0] - dv;
        if (V <= 1.0) V = v[0] + dv;
    }
    // Output
    // V must be >1 and <=1e5
    V = min(max(V, 1.0001), 1e5);
    printf("%.5f %d\n", V, N);
    for (int i = 0; i < N; ++i) {
        printf("%.2f %.2f %.2f\n", a[i], b[i], h[i]);
    }
    return 0;
}
