#include "testlib.h"
#include <array>
#include <set>
#include <vector>
#include <numeric>

using namespace std;
using u32 = unsigned int;
using u64 = unsigned long long;
using i64 = long long;

struct Vec2I {
    int x, y;
    constexpr bool operator==(const Vec2I& o) const { return x == o.x && y == o.y; }
    constexpr bool is_upper() const { return y > 0 || (y == 0 && x >= 0); }
};

constexpr i64 cross(const Vec2I& a, const Vec2I& b) { return i64(a.x)*i64(b.y) - i64(a.y)*i64(b.x); }

vector<int> zero_sum(int n, int b) {
    vector<int> x = rnd.distinct(n, b);
    int xmin = b, xmax = -1;
    for (int i = 0; i < n; i++) {
        xmin = min(xmin, x[i]);
        xmax = max(xmax, x[i]);
    }
    
    vector<int> xl, xr;
    
    xl.push_back(xmin); xr.push_back(xmin);
    for (int i = 0; i < n; i++) {
        if (x[i] == xmin || x[i] == xmax) { continue; }
        
        if (rnd.next(2)) { xl.push_back(x[i]); }
        else { xr.push_back(x[i]); }
    }
    xl.push_back(xmax); xr.push_back(xmax);
    
    vector<int> res;
    res.reserve(n);
    for (int i = 0; i < xl.size()-1; i++) { res.push_back(xl[i+1] - xl[i]); }
    for (int i = 0; i < xr.size()-1; i++) { res.push_back(xr[i] - xr[i+1]); }

    return res;
}

vector<Vec2I> convex_poly(int n, int b) {
    auto cmp = [](const Vec2I& a, const Vec2I& b) {
        if (a.is_upper() != b.is_upper()) { return a.is_upper(); }
        return cross(a, b) > 0;
    };

    while (true) {
        set<Vec2I, decltype(cmp)> delta(cmp);
        while (true) {
            auto xs = zero_sum(n, b);
            auto ys = zero_sum(n, b);
            shuffle(ys.begin(), ys.end());
            
            bool good = true;
            for (int i = 0; i < n; i++) {
                if (xs[i] == 0 && ys[i] == 0) { good = false; break; }
                if (delta.count({ xs[i], ys[i] })) { good = false; break; }
                delta.insert({ xs[i], ys[i] });
            }
            
            if (!good) {
                delta.clear();
                continue;
            }
            
            break;
        }
        
        vector<Vec2I> hull;
        hull.reserve(n);
        
        int xavg = 0, yavg = 0;
        
        int x = 0, y = 0;
        for (const auto& [dx, dy] : delta) {
            hull.push_back({ x, y });
            xavg += x; yavg += y;
            x += dx; y += dy;
        }
        
        xavg /= int(hull.size());
        yavg /= int(hull.size());

        bool retry = false;
        for (auto& [x, y] : hull) {
            x -= xavg; y -= yavg;
            if (abs(x) > b || abs(y) > b) { retry = true; break; }
        }
        
        if (retry) { continue; }

        return hull;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 8);
    println(n);
    auto v = convex_poly(n, 10000000);
    for (auto& [x, y] : v) {
        printf("%d %d\n", x, y);
    }

    return 0;
}
