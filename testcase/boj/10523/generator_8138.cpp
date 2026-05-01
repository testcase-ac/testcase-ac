#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for n: mostly small, sometimes medium
    int n;
    if (rnd.next(0,9) == 0)
        n = rnd.next(30, 50);
    else
        n = rnd.next(1, 25);
    int p = rnd.next(20, 100);
    // required points on a line
    int k = (p * n + 99) / 100;
    // decide possible or impossible
    bool possible;
    if (k <= 2) {
        // impossible to have no line through k<=2 points
        possible = true;
    } else {
        possible = rnd.next(0, 1);
    }
    vector<pair<ll,ll>> pts;
    pts.reserve(n);
    const ll MAXC = 1000000000LL;
    if (possible) {
        // generate a line with at least k points
        int linetype = rnd.next(0, 2); // 0=horiz,1=vert,2=general
        ll x0, y0, dx, dy;
        if (linetype == 0) {
            // horizontal: y=y0
            y0 = rnd.next(0LL, MAXC);
            x0 = rnd.next(0LL, MAXC - k);
            dx = 1; dy = 0;
        } else if (linetype == 1) {
            // vertical: x=x0
            x0 = rnd.next(0LL, MAXC);
            y0 = rnd.next(0LL, MAXC - k);
            dx = 0; dy = 1;
        } else {
            // general slope
            dx = rnd.next(1, 5);
            dy = rnd.next(1, 5);
            ll g = gcd(dx, dy);
            dx /= g; dy /= g;
            x0 = rnd.next(0LL, MAXC - dx * (k + 1));
            y0 = rnd.next(0LL, MAXC - dy * (k + 1));
        }
        set<pair<ll,ll>> used;
        // generate k collinear points
        for (int i = 0; i < k; i++) {
            ll x = x0 + dx * i;
            ll y = y0 + dy * i;
            pts.emplace_back(x, y);
            used.emplace(x, y);
        }
        // fill rest randomly, avoiding that line
        while ((int)pts.size() < n) {
            ll x = rnd.next(0LL, MAXC);
            ll y = rnd.next(0LL, MAXC);
            if (used.count({x, y})) continue;
            // check collinearity: (x-x0,y-y0) cross (dx,dy) != 0
            if ((x - x0) * dy == (y - y0) * dx) continue;
            used.emplace(x, y);
            pts.emplace_back(x, y);
        }
    } else {
        // impossible: use parabola so no 3 collinear, and k>=3
        // use points (i, i^2)
        for (int i = 1; i <= n; i++) {
            ll x = i;
            ll y = 1LL * i * i;
            pts.emplace_back(x, y);
        }
    }
    // shuffle points
    shuffle(pts.begin(), pts.end());
    // output
    println(n);
    println(p);
    for (auto &pr : pts) {
        println(pr.first, pr.second);
    }
    return 0;
}
