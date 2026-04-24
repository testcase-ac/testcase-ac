/* generator code */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const double PI = acos(-1.0);

    while (true) {
        /* -------- hyper‑parameters for diversity -------- */
        int  N       = rnd.next(3, 8);              // tiny, hand‑checkable
        int  R_raw   = rnd.next(8, 30);            // radius, before scaling
        int  SCALE   = 10;                        // keep integers big enough
        long long R  = 1LL * R_raw * SCALE;         // actual radius (≤50 000)

        long long shiftX = rnd.next(-50, 50); // keep final |coord| < 100 000
        long long shiftY = rnd.next(-50, 50);

        double base = rnd.next() * 2.0 * PI;        // rotate whole polygon

        vector<pair<long long,long long>> pts;
        pts.reserve(N);
        bool bad = false;

        for (int i = 0; i < N; ++i) {
            double ang = base + 2.0 * PI * i / N;   // equally spaced ⇒ convex
            long long xi = llround(cos(ang) * R) + shiftX;
            long long yi = llround(sin(ang) * R) + shiftY;

            if (abs(xi) > 100000 || abs(yi) > 100000) { bad = true; break; }

            pts.emplace_back(xi, yi);
        }
        if (bad) continue;                          // coordinates out of bounds

        /* -------- duplicate safety (extremely unlikely) -------- */
        std::set<pair<long long,long long>> chk(pts.begin(), pts.end());
        if ((int)chk.size() != N) continue;

        /* ---------- success: emit input & exit ---------- */
        println(N);
        for (auto &p : pts) println(p.first, p.second);
        return 0;
    }
}
