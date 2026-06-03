#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? 1 : rnd.next(2, 18);

    vector<int> h(n), a(n);

    if (mode == 0) {
        h[0] = rnd.next(1, 100000);
        a[0] = rnd.next(1, 10000);
    } else if (mode == 1) {
        int growth = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(1, 60);
            a[i] = growth;
        }
    } else if (mode == 2) {
        int start = rnd.next(1, 200);
        int step = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(1, 100);
            a[i] = min(10000, start + i * step);
        }
    } else if (mode == 3) {
        int start = rnd.next(1, 200);
        int step = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(1, 100);
            a[i] = min(10000, start + (n - 1 - i) * step);
        }
    } else if (mode == 4) {
        int lowH = rnd.next(1, 40);
        int highH = rnd.next(lowH, min(100000, lowH + rnd.next(0, 200)));
        int lowA = rnd.next(1, 40);
        int highA = rnd.next(lowA, min(10000, lowA + rnd.next(0, 200)));
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(lowH, highH);
            a[i] = rnd.next(lowA, highA);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(1, 100);
            a[i] = rnd.next(1, 120);
        }
        int special = rnd.next(1, min(n, 4));
        for (int i = 0; i < special; ++i) {
            int pos = rnd.next(n);
            h[pos] = rnd.next(90000, 100000);
            a[pos] = rnd.next(9000, 10000);
        }
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<int> outH(n), outA(n);
    for (int i = 0; i < n; ++i) {
        outH[i] = h[order[i]];
        outA[i] = a[order[i]];
    }

    println(n);
    println(outH);
    println(outA);

    return 0;
}
