#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 80);
    vector<int> c(n);

    if (mode == 0) {
        int color = rnd.next(0, 1);
        fill(c.begin(), c.end(), color);
    } else if (mode == 1) {
        int start = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) c[i] = (start + i) % 2;
    } else if (mode == 2) {
        int color = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(1, 5) == 1) color ^= 1;
            c[i] = color;
        }
    } else if (mode == 3) {
        int color = rnd.next(0, 1);
        int pos = 0;
        while (pos < n) {
            int len = min(n - pos, rnd.next(1, 8));
            for (int j = 0; j < len; ++j) c[pos + j] = color;
            pos += len;
            color ^= 1;
        }
    } else if (mode == 4) {
        int start = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) c[i] = (start + i / 2) % 2;
    } else {
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0, 1);
        if (n >= 8) {
            int base = rnd.next(0, 1);
            c[n - 8] = base ^ 1;
            c[n - 7] = base;
            c[n - 6] = base ^ 1;
            c[n - 5] = base ^ 1;
            c[n - 4] = base;
            c[n - 3] = base;
            c[n - 2] = base;
            c[n - 1] = rnd.next(0, 1);
        }
    }

    println(n);
    for (int color : c) println(color);

    return 0;
}
