#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of polygon vertices
    int N = rnd.next(3, 10);
    // Star-shaped polygon hyper-parameters
    int cx = rnd.next(100, 1000);
    int cy = rnd.next(100, 1000);
    int Rmin = rnd.next(5, 50);
    int Rmax = rnd.next(Rmin + 1, 100);
    // Generate vertices by polar angle sorting
    const double PI = acos(-1.0);
    vector<pair<long long,long long>> poly;
    for (int i = 0; i < N; i++) {
        double ang = 2 * PI * i / N;
        // Bias radius toward extremes sometimes
        int t = rnd.next(-1, 1);
        int hi = Rmax - Rmin + 1;
        int dr = rnd.wnext(hi, t);
        int r = Rmin + dr;
        long long x = llround(cx + r * cos(ang));
        long long y = llround(cy + r * sin(ang));
        poly.emplace_back(x, y);
    }
    // Queries: one inside (center), one on boundary (a vertex), one outside
    vector<pair<long long,long long>> qs;
    // inside
    qs.emplace_back(cx, cy);
    // on boundary: pick a random vertex
    int bi = rnd.next(0, N-1);
    qs.emplace_back(poly[bi].first, poly[bi].second);
    // outside: to the right of center
    int D = rnd.next(1, 50);
    qs.emplace_back((long long)cx + Rmax + D, cy);
    // Shuffle query order for variability
    shuffle(qs.begin(), qs.end());
    // Output
    println(N);
    for (auto &p : poly) println(p.first, p.second);
    for (auto &q : qs) println(q.first, q.second);
    return 0;
}
