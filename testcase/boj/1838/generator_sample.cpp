#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    if (mode == 6) {
        n = rnd.next(60, 180);
    }

    vector<long long> a(n);
    long long base = rnd.next(-1000000, 1000000);
    long long step = rnd.next(1, 1000);
    for (int i = 0; i < n; ++i) {
        a[i] = base + step * i;
    }

    if (mode == 0) {
        // Already sorted.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int shift = rnd.next(1, n);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, max(0, n - 2));
            swap(a[pos], a[pos + 1]);
        }
    } else if (mode == 4) {
        int block = rnd.next(1, n);
        reverse(a.begin(), a.begin() + block);
    } else if (mode == 5) {
        shuffle(a.begin(), a.end());
    } else {
        vector<long long> extremes;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                extremes.push_back(-2147483647LL + i / 2);
            } else {
                extremes.push_back(2147483647LL - i / 2);
            }
        }
        a = extremes;
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
