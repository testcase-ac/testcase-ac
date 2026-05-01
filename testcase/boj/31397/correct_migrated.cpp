#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>

using namespace std;
using i64 = long long;
using fl = long double;

template <class T>
struct Vec2 {
    T x, y;
    constexpr fl norm() const { return hypot(x, y); }
    constexpr Vec2 operator-(const Vec2& r) const { return { x - r.x, y - r.y }; }
};
struct Parts { int i; fl f; }; // integer part & frac part

using Vec2D = Vec2<fl>;
using Vec2I32 = Vec2<int>;

constexpr Vec2D to_d(const Vec2I32& v) { return Vec2D { fl(v.x), fl(v.y) }; }

template <class T>
constexpr Vec2D lerp(const Vec2<T>& a, const Vec2<T>& b, fl t) { return { fl(a.x)*(1-t) + fl(b.x)*t, fl(a.y)*(1-t) + fl(b.y)*t }; }

constexpr fl cross(const Vec2D& a, const Vec2D& b) { return a.x*b.y - a.y*b.x; }
constexpr i64 cross(const Vec2I32& a, const Vec2I32& b) { return i64(a.x)*i64(b.y) - i64(a.y)*i64(b.x); }

array<Vec2I32, 200'000> arr;
array<fl, 200'000> len;
array<fl, 200'001> len_psum;
array<i64, 200'001> cross_psum;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(16);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].x >> arr[i].y;
    }

    for (int i = 0; i < n-1; i++) { len[i] = (arr[i+1] - arr[i]).norm(); }
    len[n-1] = (arr[0] - arr[n-1]).norm();

    for (int i = 1; i <= n; i++) { len_psum[i] = len_psum[i-1] + len[i-1]; }
    fl perim = len_psum[n];

    for (int i = 1; i < n; i++) { cross_psum[i] = cross_psum[i-1] + cross(arr[i-1], arr[i]); }
    cross_psum[n] = cross_psum[n-1] + cross(arr[n-1], arr[0]);
    i64 area_x2 = cross_psum[n];

    auto walk = [&](fl l) -> Parts {
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (l <= len_psum[mid+1]) {
                hi = mid;
            } else {
                lo = mid+1;
            }
        }
        
        return { lo, (l - len_psum[lo])/len[lo] };
    };

    auto wrap = [&](int i) { return i >= n ? i-n : i; };

    auto cut_area_x2 = [&](fl l) -> fl {
        Parts u = walk(l);
        Parts v = walk(l + perim*0.5);
        
        Vec2D start = lerp(arr[u.i], arr[wrap(u.i+1)], u.f);
        Vec2D end = lerp(arr[v.i], arr[wrap(v.i+1)], v.f);

        fl res = cross(start, to_d(arr[wrap(u.i+1)]));
        res += cross_psum[v.i] - cross_psum[u.i+1];
        res += cross(to_d(arr[v.i]), end);
        res += cross(end, start);

        return res;
    };

    // diff > 0: ccw greater, diff < 0: cw greater
    auto diff = [&](fl t) -> fl { return 2*cut_area_x2(t) - area_x2; };

    constexpr int max_iter = 100;
    constexpr fl ftol = 1e-9;

    fl lo = 0, hi = perim*0.5;
    // diff(0) = -diff(perim*0.5)
    // intermediate value theorem guarantees at least one root between 0 and (0 + perim*0.5)
    bool decr = diff(lo) > 0;
    for (int _ = 0; _ < max_iter; _++) {
        fl mid = (lo + hi)*0.5;
        fl mdiff = diff(mid);
        if (abs(mdiff) < ftol) {
            lo = mid;
            break;
        } else if ((decr && mdiff < 0) || (!decr && mdiff > 0)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    Parts u = walk(lo), v = walk(lo + perim*0.5);
    cout << "YES\n";
    cout << u.i+1 << " " << u.f << "\n";
    cout << v.i+1 << " " << v.f << "\n";

    return 0;
}
