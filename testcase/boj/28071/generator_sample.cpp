#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
        k = rnd.next(1, 12);
        int value = rnd.next(1, 300);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(1, 20);
        k = rnd.next(2, 60);
        int g = rnd.next(2, 10);
        while (k % g == 0) {
            g = rnd.next(2, 10);
        }
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, 300 / g) * g;
            a.push_back(x);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        m = rnd.next(1, 30);
        k = rnd.next(2, 50);
        int base = rnd.next(1, 300);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3, 3) * k;
            int x = base + delta;
            while (x < 1) x += k;
            while (x > 300) x -= k;
            a.push_back(x);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 16);
        m = rnd.next(10, 60);
        k = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(rnd.next(1, 300 / k) * k);
            } else {
                a.push_back(rnd.next(1, 300));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        m = rnd.next(150, 300);
        k = rnd.next(150, 300);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<int>{1, 2, 3, k - 1, k, 300}));
        }
    } else {
        n = rnd.next(6, 20);
        m = rnd.next(1, 80);
        k = rnd.next(2, 120);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 300));
        }
    }

    shuffle(a.begin(), a.end());

    println(n, m, k);
    println(a);

    return 0;
}
