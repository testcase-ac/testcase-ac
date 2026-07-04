#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeCase(int mode, int k) {
    vector<int> a(k);

    if (mode == 0) {
        for (int &x : a) x = rnd.next(1, 20);
    } else if (mode == 1) {
        int value = rnd.next(1, 10000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        int cur = rnd.next(1, 30);
        for (int i = 0; i < k; ++i) {
            cur = min(10000, cur + rnd.next(0, 80));
            a[i] = cur;
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        int low = rnd.next(1, 30);
        int high = rnd.next(9000, 10000);
        for (int i = 0; i < k; ++i) a[i] = (i % 2 == 0 ? low : high);
    } else {
        for (int i = 0; i < k; ++i) {
            if (rnd.next(100) < 70) {
                a[i] = rnd.next(1, 200);
            } else {
                a[i] = rnd.next(8000, 10000);
            }
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int k;

        if (mode == 1 && rnd.next(100) < 25) {
            k = rnd.next(120, 220);
        } else if (rnd.next(100) < 30) {
            k = rnd.next(3, 5);
        } else {
            k = rnd.next(6, 30);
        }

        vector<int> a = makeCase(mode, k);
        println(k);
        println(a);
    }

    return 0;
}
