#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // 20% chance to generate a simple rectangle
    if (rnd.next(1, 5) == 1) {
        int w = rnd.next(1, 10);
        int h = rnd.next(1, 10);
        int x0 = rnd.next(-1000, 1000);
        int y0 = rnd.next(-1000, 1000);
        // CCW rectangle: bottom-left, bottom-right, top-right, top-left
        vector<pair<int,int>> P = {
            {x0, y0},
            {x0 + w, y0},
            {x0 + w, y0 + h},
            {x0, y0 + h}
        };
        // reverse to CW
        reverse(P.begin(), P.end());
        println(4);
        for (auto &p : P) println(p.first, p.second);
        return 0;
    }
    // Histogram-style simple orthogonal polygon (x-monotone)
    int k = rnd.next(1, 8);  // number of segments
    vector<int> w(k+1), h(k+1), xs(k+1);
    for (int i = 1; i <= k; i++) {
        w[i] = rnd.next(1, 10);
    }
    // Heights >=1, introduce some correlation
    h[1] = rnd.next(1, 20);
    for (int i = 2; i <= k; i++) {
        if (rnd.next(0, 1) == 0) h[i] = h[i-1];
        else h[i] = rnd.next(1, 20);
    }
    xs[0] = 0;
    for (int i = 1; i <= k; i++) xs[i] = xs[i-1] + w[i];
    int x0 = rnd.next(-1000, 1000);
    int y0 = rnd.next(-1000, 1000);
    vector<pair<int,int>> P;
    // start CCW: bottom-left, bottom-right
    P.emplace_back(x0 + xs[0], y0);
    P.emplace_back(x0 + xs[k], y0);
    // rise up at rightmost
    P.emplace_back(x0 + xs[k], y0 + h[k]);
    // go along top contour
    for (int i = k; i >= 2; i--) {
        // horizontal move to the left at height h[i]
        P.emplace_back(x0 + xs[i-1], y0 + h[i]);
        // vertical move to height h[i-1] if needed
        if (h[i] != h[i-1])
            P.emplace_back(x0 + xs[i-1], y0 + h[i-1]);
    }
    // final horizontal to the leftmost at height h[1]
    P.emplace_back(x0 + xs[0], y0 + h[1]);
    // reverse to CW
    reverse(P.begin(), P.end());
    // rotate start point randomly
    int n = P.size();
    int shift = rnd.next(0, n - 1);
    vector<pair<int,int>> Q;
    Q.reserve(n);
    for (int i = 0; i < n; i++)
        Q.push_back(P[(i + shift) % n]);
    // output
    println(n);
    for (auto &pr : Q) println(pr.first, pr.second);
    return 0;
}
