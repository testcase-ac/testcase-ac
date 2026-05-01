#include "testlib.h"
#include <cmath>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int scen = rnd.next(0, 4);
    set<pair<int,int>> s;
    if (scen == 0) {
        // Pure random scatter
        int N = rnd.next(3, 30);
        while ((int)s.size() < N) {
            int x = rnd.next(-10, 10);
            int y = rnd.next(-10, 10);
            s.emplace(x, y);
        }
    } else if (scen == 1) {
        // Circle + interior
        int N = rnd.next(3, 30);
        int H = rnd.next(3, min(N, 10));
        double R = rnd.next(5.0, 20.0);
        double pi = acos(-1.0);
        // Hull points
        for (int i = 0; i < H; i++) {
            double base = 2*pi*i/H;
            double jitter = rnd.next(-pi/H, pi/H);
            double ang = base + jitter;
            int x = int(round(R * cos(ang)));
            int y = int(round(R * sin(ang)));
            s.emplace(x, y);
        }
        // Interior points
        for (int i = 0; i < N - H; i++) {
            double ang = rnd.next(0.0, 2*pi);
            double r = R * pow(rnd.next(), 0.5);
            int x = int(round(r * cos(ang)));
            int y = int(round(r * sin(ang)));
            s.emplace(x, y);
        }
    } else if (scen == 2) {
        // Rectangle perimeter
        int W = rnd.next(1, 10);
        int H = rnd.next(1, 10);
        for (int x = 0; x <= W; x++) {
            s.emplace(x, 0);
            s.emplace(x, H);
        }
        for (int y = 0; y <= H; y++) {
            s.emplace(0, y);
            s.emplace(W, y);
        }
    } else if (scen == 3) {
        // Almost collinear
        int L = rnd.next(3, 20);
        int c = rnd.next(-10, 10);
        bool horiz = rnd.next(0, 1) == 0;
        for (int i = 0; i < L; i++) {
            int d = rnd.next(-10, 10);
            if (horiz) s.emplace(d, c);
            else       s.emplace(c, d);
        }
        int extra = rnd.next(1, min(5, L-2));
        for (int i = 0; i < extra; i++) {
            int d = rnd.next(-10, 10);
            int off = rnd.any(vector<int>{1,2, -1, -2});
            if (horiz) s.emplace(d, c + off);
            else       s.emplace(c + off, d);
        }
    } else {
        // Two parallel lines + interior
        int L = rnd.next(3, 15);
        for (int i = 0; i < L; i++) {
            int x = rnd.next(-10, 10);
            s.emplace(x, 0);
            s.emplace(x, 2);
        }
        int M = rnd.next(0, L);
        for (int i = 0; i < M; i++) {
            int x = rnd.next(-10, 10);
            s.emplace(x, 1);
        }
    }
    // Ensure at least 3 points
    while ((int)s.size() < 3) {
        int x = rnd.next(-5, 5), y = rnd.next(-5, 5);
        s.emplace(x, y);
    }
    vector<pair<int,int>> pts(s.begin(), s.end());
    shuffle(pts.begin(), pts.end());
    println(pts.size());
    for (auto &p : pts)
        println(p.first, p.second);
    return 0;
}
