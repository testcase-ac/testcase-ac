#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;
using i64 = long long;

struct Point { i64 x, y, val; };
struct Segment { i64 x1, x2, y; };

constexpr i64 cross(const Point& a, const Point& b) {
    return a.x*b.y - b.x*a.y;
}

constexpr int MAX_N = 2000;

array<Segment, MAX_N> arr;
array<Point, 2*MAX_N> points;
array<int, 2*MAX_N> ord;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        i64 x1, x2, y;
        cin >> x1 >> x2 >> y;
        if (x2 < x1) { swap(x1, x2); }
        arr[i] = { x1, x2, -y };
    }
    
    i64 best = 0;
    for (int i = 0; i < n; i++) {
        auto [i_x1, i_x2, i_y] = arr[i];

        int m = 0;
        for (int j = 0; j < n; j++) {
            auto [j_x1, j_x2, j_y] = arr[j];
            i64 sz = j_x2 - j_x1;

            if (j_y == i_y) { continue; }

            int r, l, y;
            if (j_y > i_y) {
                r = j_x2 - i_x1;
                l = j_x1 - i_x1;
                y = j_y - i_y;
            } else {
                r = i_x1 - j_x1;
                l = i_x1 - j_x2;
                y = i_y - j_y;
            }

            points[m++] = { l, y, -sz };
            points[m++] = { r, y, sz };
        }
        
        iota(ord.begin(), ord.begin()+m, 0);
        sort(ord.begin(), ord.begin()+m, [&](int a, int b) {
            i64 cr = cross(points[a], points[b]);
            return cr > 0 || (cr == 0 && points[a].val > points[b].val);
        });

        i64 cur_val = i_x2 - i_x1;
        best = max(best, cur_val);
        for (int jidx = 0; jidx < m; jidx++) {
            int j = ord[jidx];
            auto [j_x, j_y, j_v] = points[j];
            
            cur_val += j_v;
            best = max(best, cur_val);
        }
    }

    cout << best << "\n";

    return 0;
}
