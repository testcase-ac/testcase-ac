#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Student {
    int a;
    int l;
    int r;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(60, 180);
    } else {
        n = rnd.next(2, 18);
    }

    vector<Student> s(n + 1);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            s[i].a = rnd.next(1, 1000000000);
            s[i].l = n;
            s[i].r = n;
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            s[i].a = (i % 2 == 0 ? 1000000000 - rnd.next(0, 20) : 1 + rnd.next(0, 20));
            s[i].l = 1;
            s[i].r = 1;
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            s[i].a = rnd.next(1, 1000000000);
            s[i].l = rnd.next(1, n);
            s[i].r = n;
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            s[i].a = rnd.next(1, 60);
            s[i].l = min(n, rnd.next(1, 3));
            s[i].r = rnd.next(s[i].l, min(n, s[i].l + rnd.next(0, 4)));
        }
    } else if (mode == 4) {
        for (int i = 1; i <= n; ++i) {
            int distance = max(i - 1, n - i);
            s[i].a = rnd.next(1, 1000000000);
            s[i].l = max(1, distance);
            s[i].r = rnd.next(s[i].l, n);
        }
    } else if (mode == 5) {
        int base = rnd.next(1, 1000);
        for (int i = 1; i <= n; ++i) {
            s[i].a = min(1000000000, base + rnd.next(0, 7));
            s[i].l = rnd.next(1, n);
            s[i].r = rnd.next(s[i].l, n);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            s[i].a = rnd.next(1, 1000000000);
            s[i].l = rnd.next(1, n);
            s[i].r = rnd.next(s[i].l, n);
        }
    }

    if (rnd.next(0, 3) == 0) {
        int x = rnd.next(1, n);
        s[x].a = rnd.any(vector<int>{1, 1000000000});
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(s[i].a, s[i].l, s[i].r);
    }

    return 0;
}
