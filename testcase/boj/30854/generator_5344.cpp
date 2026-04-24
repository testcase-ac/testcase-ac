#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of vertical edges h (so m = 2*h)
    int h = rnd.next(2, 5);
    int m = 2 * h;

    // Hyper-parameters for diversity
    int t_w = rnd.any(vector<int>{-1, 0, 1});    // width bias
    int t_h = rnd.any(vector<int>{-1, 0, 1});    // height bias
    int t_n = rnd.any(vector<int>{-1, 0, 1});    // number of points bias

    // Generate widths of the (h-1) horizontal spans
    vector<int> w(h - 1);
    for (int i = 0; i < h - 1; i++) {
        // w in [1..10], biased
        w[i] = rnd.wnext(10, t_w) + 1;
    }

    // X-coordinates of vertical edges
    vector<int> x(h);
    x[0] = 0;
    for (int i = 1; i < h; i++) {
        x[i] = x[i - 1] + w[i - 1];
    }

    // Heights for the (h-1) top horizontal edges
    vector<int> y(h - 1);
    for (int i = 0; i < h - 1; i++) {
        // y in [1..20], biased
        y[i] = rnd.wnext(20, t_h) + 1;
    }

    // Build v-array of size m: odd indices are x, even are y (0-based: even=>x, odd=>y)
    vector<int> v(m);
    v[0] = 0;
    for (int j = 1; j < h; j++) {
        v[2*j] = x[j];
    }
    for (int j = 0; j < h - 1; j++) {
        v[2*j + 1] = y[j];
    }
    v[m - 1] = 0;  // last y back to road

    // Number of points
    int n = rnd.wnext(11, t_n); // in [0..10], biased

    // Generate points inside or on boundary
    vector<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        // choose a horizontal segment [x[j], x[j+1]] with height y[j]
        int seg = rnd.next(0, h - 2);
        int px = rnd.next(x[seg], x[seg+1]);
        int py = rnd.next(0, y[seg]);
        pts.emplace_back(px, py);
    }

    // Output
    println(m, n);
    println(v);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
