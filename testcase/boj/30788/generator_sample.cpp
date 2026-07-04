#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int angleNearBoundary() {
    static const int choices[] = {0, 1, 2, 89, 90, 91, 178, 179};
    return choices[rnd.next(0, 7)];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 25);
        if (n % 2 == 0) {
            ++n;
        }
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(0, 179);
        }
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 12);
        a.resize(n);
        for (int i = 0; i < n / 2; ++i) {
            int x = rnd.next(0, 179);
            a[2 * i] = x;
            a[2 * i + 1] = x;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = 2 * rnd.next(2, 15);
        a.resize(n);
        int sumFirst = 0;
        int sumSecond = 0;
        for (int i = 0; i < n / 2; ++i) {
            a[i] = rnd.next(0, 179);
            sumFirst = (sumFirst + a[i]) % 180;
        }
        for (int i = n / 2; i + 1 < n; ++i) {
            a[i] = rnd.next(0, 179);
            sumSecond = (sumSecond + a[i]) % 180;
        }
        a[n - 1] = (sumFirst - sumSecond + 180) % 180;
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        n = 2 * rnd.next(1, 20);
        int paletteSize = rnd.next(1, 5);
        vector<int> palette(paletteSize);
        for (int& x : palette) {
            x = rnd.next(0, 179);
        }
        a.resize(n);
        for (int& x : a) {
            x = rnd.any(palette);
        }
    } else if (mode == 4) {
        n = 2 * rnd.next(1, 18);
        a.resize(n);
        for (int& x : a) {
            x = angleNearBoundary();
        }
    } else {
        n = 2 * rnd.next(80, 250);
        a.resize(n);
        int base = rnd.next(0, 179);
        int step = rnd.next(1, 17);
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(-2, 2);
            a[i] = (base + step * i + jitter + 540) % 180;
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
