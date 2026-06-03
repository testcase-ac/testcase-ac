#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode <= 4) {
        n = rnd.next(6, 20);
    } else {
        n = rnd.next(21, 50);
    }

    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, 1000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int current = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(0, 3);
            a[i] = min(current, 1000);
        }
    } else if (mode == 2) {
        int current = rnd.next(980, 1000);
        for (int i = 0; i < n; ++i) {
            a[i] = max(1, current);
            current -= rnd.next(0, 4);
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 25);
        int width = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, min(1000, lo + width));
    } else if (mode == 4) {
        vector<int> values;
        int groups = rnd.next(2, min(8, n));
        int base = rnd.next(1, 1000 - groups + 1);
        for (int g = 0; g < groups; ++g) {
            int repeats = rnd.next(1, max(1, n / groups + 3));
            for (int k = 0; k < repeats && (int)values.size() < n; ++k)
                values.push_back(base + g);
        }
        while ((int)values.size() < n) values.push_back(base + rnd.next(0, groups - 1));
        shuffle(values.begin(), values.end());
        a = values;
    } else if (mode == 5) {
        int lo = rnd.next(1, 1000 - n + 1);
        for (int i = 0; i < n; ++i) a[i] = lo + i;
        shuffle(a.begin(), a.end());
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a[i] = rnd.next(990, 1000);
            } else {
                a[i] = rnd.next(1, 12);
            }
        }
    }

    println(n);
    println(a);

    return 0;
}
