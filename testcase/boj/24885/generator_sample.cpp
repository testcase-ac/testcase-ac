#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    int m = rnd.next(0, 1000);
    int k = rnd.next(1, 4);
    int mode = rnd.next(7);

    vector<int> p(n);
    if (mode == 0) {
        int price = rnd.next(100, 1000);
        fill(p.begin(), p.end(), price);
    } else if (mode == 1) {
        int low = rnd.next(100, 400);
        int high = rnd.next(600, 1000);
        for (int i = 0; i < n; ++i) {
            p[i] = (i % 2 == 0 ? low : high);
        }
    } else if (mode == 2) {
        int low = rnd.next(100, 250);
        int step = rnd.next(20, 120);
        for (int i = 0; i < n; ++i) {
            p[i] = min(1000, low + i * step + rnd.next(0, 30));
        }
    } else if (mode == 3) {
        int high = rnd.next(700, 1000);
        int step = rnd.next(20, 120);
        for (int i = 0; i < n; ++i) {
            p[i] = max(100, high - i * step - rnd.next(0, 30));
        }
    } else if (mode == 4) {
        int cheap = rnd.next(100, 180);
        int mid = rnd.next(250, 650);
        int expensive = rnd.next(800, 1000);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.any(vector<int>{cheap, mid, expensive});
        }
    } else if (mode == 5 && n >= 3) {
        int valley = rnd.next(1, n - 2);
        int left = rnd.next(600, 1000);
        int bottom = rnd.next(100, 300);
        int right = rnd.next(600, 1000);
        for (int i = 0; i < n; ++i) {
            if (i < valley) {
                p[i] = max(100, left - i * rnd.next(20, 90));
            } else if (i == valley) {
                p[i] = bottom;
            } else {
                p[i] = min(1000, bottom + (i - valley) * rnd.next(50, 180));
            }
        }
        p[n - 1] = max(p[n - 1], right);
    } else {
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(100, 1000);
        }
    }

    println(n, m, k);
    println(p);

    return 0;
}
