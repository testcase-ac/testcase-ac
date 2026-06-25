#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 30);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, min(n, 3));
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(max(1, n - 3), n);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        int hi = rnd.next(1, min(n, 5));
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, hi);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int leftLen = i;
            int rightLen = n - 1 - i;
            if (leftLen > 0 && rightLen > 0) {
                a[i] = rnd.next(0, 1) ? leftLen : rightLen;
            } else {
                a[i] = max(leftLen, rightLen);
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, n);

        int pos = 0;
        while (pos < n) {
            int remaining = n - pos;
            int len = rnd.next(1, min(remaining, 6));
            if (remaining - len == 1) ++len;
            if (len > 1) {
                if (rnd.next(0, 1)) {
                    a[pos] = len - 1;
                } else {
                    a[pos + len - 1] = len - 1;
                }
            }
            pos += len;
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            int distanceToEdge = min(i, n - 1 - i);
            a[i] = rnd.next(1, max(1, distanceToEdge + 1));
        }
    } else {
        n = rnd.next(40, 100);
        a.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) a[i] = rnd.next(1, n);
        }
    }

    println(n);
    println(a);

    return 0;
}
