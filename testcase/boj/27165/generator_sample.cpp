#include "testlib.h"

#include <vector>
using namespace std;

int safeCount() {
    int value = rnd.next(0, 5);
    if (value == 0) return 0;
    if (value == 1) return 10;
    return rnd.next(2, 5);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 25);
    int x = rnd.next(1, n);
    vector<int> a(n + 1);

    if (mode == 0) {
        x = rnd.next(1, n);
        int from = rnd.next(0, n - x);
        int to = from + x;

        for (int i = 0; i <= n; ++i) a[i] = safeCount();
        a[from] = rnd.next(3, 10);
        a[to] = 1;
    } else if (mode == 1) {
        x = rnd.next(1, n);
        for (int i = 0; i <= n; ++i) a[i] = rnd.next(0, 1) ? 0 : rnd.next(2, 10);
    } else if (mode == 2) {
        x = n;
        for (int i = 0; i <= n; ++i) a[i] = safeCount();
        a[0] = rnd.next(1, 10);
        if (rnd.next(0, 1)) {
            a[0] = rnd.next(3, 10);
            a[n] = 1;
        }
    } else {
        n = rnd.next(2, 40);
        x = rnd.next(1, n);
        a.assign(n + 1, 0);
        for (int i = 0; i <= n; ++i) {
            int choice = rnd.next(0, 9);
            if (choice <= 2) a[i] = 0;
            else if (choice <= 5) a[i] = 1;
            else if (choice == 6) a[i] = 10;
            else a[i] = rnd.next(2, 9);
        }
    }

    if (a[0] == 0) a[0] = rnd.next(1, 10);

    println(n);
    println(a);
    println(x);

    return 0;
}
