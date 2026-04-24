#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small size
    int N = rnd.next(1, 10);
    int X = rnd.next(1, N);
    int maxh = rnd.next(1, 20);
    vector<int> a(N);
    // choose a pattern type for diversity
    int type = rnd.next(0, 5);
    if (type == 0) {
        // uniform random heights
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, maxh);
    } else if (type == 1) {
        // non-decreasing
        if (N == 1) {
            a[0] = rnd.next(1, maxh);
        } else {
            for (int i = 0; i < N; i++)
                a[i] = 1 + (i * (maxh - 1)) / (N - 1);
        }
    } else if (type == 2) {
        // non-increasing
        if (N == 1) {
            a[0] = rnd.next(1, maxh);
        } else {
            for (int i = 0; i < N; i++)
                a[i] = 1 + ((N - 1 - i) * (maxh - 1)) / (N - 1);
        }
    } else if (type == 3) {
        // valley shape (low in middle, high at ends)
        double center = (N - 1) / 2.0;
        double maxd = max(center, (double)(N - 1) - center);
        for (int i = 0; i < N; i++) {
            double frac = fabs(i - center) / maxd;
            a[i] = 1 + int(frac * (maxh - 1) + 0.5);
        }
    } else if (type == 4) {
        // peak shape (high in middle, low at ends)
        double center = (N - 1) / 2.0;
        double maxd = max(center, (double)(N - 1) - center);
        for (int i = 0; i < N; i++) {
            double frac = fabs(i - center) / maxd;
            a[i] = 1 + int((1 - frac) * (maxh - 1) + 0.5);
        }
    } else {
        // constant
        int v = rnd.next(1, maxh);
        for (int i = 0; i < N; i++)
            a[i] = v;
    }
    // output
    println(N, X);
    println(a);
    return 0;
}
