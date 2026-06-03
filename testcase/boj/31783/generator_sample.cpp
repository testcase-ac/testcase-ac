#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);

    vector<int> h(n);
    if (mode == 0) {
        int value = rnd.next(0, 20);
        fill(h.begin(), h.end(), value);
    } else if (mode == 1) {
        h[0] = rnd.next(n - 1, n + 40);
        for (int i = 1; i < n; ++i) h[i] = h[i - 1] - rnd.next(1, 4);
    } else if (mode == 2) {
        h[0] = rnd.next(1000000000 - 100, 1000000000);
        for (int i = 1; i < n; ++i) h[i] = h[i - 1] - rnd.next(0, 12);
    } else {
        h[0] = rnd.next(0, 80);
        for (int i = 1; i < n; ++i) h[i] = h[i - 1] - rnd.next(0, 8);
    }
    for (int& value : h) value = max(value, 0);

    vector<int> a(n - 1), b(n - 1);
    for (int i = 1; i < n; ++i) {
        if (mode == 3) {
            a[i - 1] = rnd.next(0, 15);
            b[i - 1] = rnd.next(0, max(0, h[0] - h[i]));
        } else if (mode == 4) {
            a[i - 1] = rnd.next(0, 30);
            b[i - 1] = rnd.next(h[0] - h[i] + 1, 1000000000);
        } else if (mode == 5) {
            a[i - 1] = rnd.any(vector<int>{0, 1, 7, 1000000000});
            b[i - 1] = rnd.any(vector<int>{0, 1, 1000000000});
        } else {
            a[i - 1] = rnd.next(0, 50);
            int gap = h[0] - h[i];
            b[i - 1] = rnd.next(0, max(100, gap + 20));
        }
    }

    println(n);
    println(h);
    println(a);
    println(b);

    return 0;
}
