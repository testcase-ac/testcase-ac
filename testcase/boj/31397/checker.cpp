#include "testlib.h"

#include <array>
#include <cmath>

using namespace std;
using i64 = long long;
using fl = double;

template <class T>
struct Vec2 {
    T x, y;
    constexpr fl norm() const { return hypot(x, y); }
    constexpr Vec2 operator-(const Vec2& r) const { return { x - r.x, y - r.y }; }
};
struct Parts { int i; fl f; };

using Vec2D = Vec2<fl>;
using Vec2I32 = Vec2<int>;

constexpr Vec2D to_d(const Vec2I32& v) { return Vec2D { fl(v.x), fl(v.y) }; }

template <class T>
constexpr Vec2D lerp(const Vec2<T>& a, const Vec2<T>& b, fl t) { return { fl(a.x)*(1-t) + fl(b.x)*t, fl(a.y)*(1-t) + fl(b.y)*t }; }

constexpr fl cross(const Vec2D& a, const Vec2D& b) { return a.x*b.y - a.y*b.x; }
constexpr i64 cross(const Vec2I32& a, const Vec2I32& b) { return i64(a.x)*i64(b.y) - i64(a.y)*i64(b.x); }

array<Vec2I32, 200'000> arr;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string yes = ouf.readWord();
    quitif(yes != "YES", _wa, "a valid cut exists: expected YES, got %s", yes.data());

    int n = inf.readInt();
    for (int i = 0; i < n; i++) {
        arr[i].x = inf.readInt();
        arr[i].y = inf.readInt();
    }
    
    fl perim = (arr[0] - arr[n-1]).norm();
    for (int i = 0; i < n-1; i++) { perim += (arr[i+1] - arr[i]).norm(); }
    
    i64 area_x2 = cross(arr[n-1], arr[0]);
    for (int i = 0; i < n-1; i++) { area_x2 += cross(arr[i], arr[i+1]); }

    fl ans_perim = perim*0.5;
    fl ans_area = area_x2*0.25;
    
    auto wrap = [&](int x) { return x >= n ? x-n : x; };

    Parts u, v;
    u.i = ouf.readInt(1, n, "j")-1; u.f = ouf.readDouble(0, 1, "alpha");
    v.i = ouf.readInt(1, n, "k")-1; v.f = ouf.readDouble(0, 1, "beta");
    
    if (u.i > v.i || (u.i == v.i && u.f > v.f)) { swap(u, v); }
    Vec2D start = lerp(arr[u.i], arr[wrap(u.i+1)], u.f);
    Vec2D end = lerp(arr[v.i], arr[wrap(v.i+1)], v.f);

    fl cut_perim = 0, cut_area = 0;
    if (u.i != v.i) {
        cut_perim = (to_d(arr[wrap(u.i+1)]) - start).norm();
        cut_area = cross(start, to_d(arr[wrap(u.i+1)]));
        for (int i = u.i+1; i < v.i; i++) {
            cut_perim += (arr[i+1] - arr[i]).norm();
            cut_area += cross(arr[i], arr[i+1]);
        }
        cut_perim += (end - to_d(arr[v.i])).norm();
        cut_area += cross(to_d(arr[v.i]), end);
        cut_area += cross(end, start);
        cut_area *= 0.5;
    } else {
        // 당연히 정답이 될 수는 없지만 혹시 모르니
        cut_perim = (end - start).norm();
        cut_area = 0;
    }

    quitif(abs(ans_perim - cut_perim) > max(1e-6, ans_perim*1e-6), _wa, "perimeter mismatch: expected %.8lf, found %.8lf out of error range", ans_perim, cut_perim);
    quitif(abs(ans_area - cut_area) > max(1e-6, ans_area*1e-6), _wa, "area mismatch: expected %.8lf, found %.8lf out of error range", ans_area, cut_area);

    quitf(_ok, "mazassumnida!!");
    return 0;
}
