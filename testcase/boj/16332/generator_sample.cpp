#include "testlib.h"

#include <vector>

using namespace std;

int pickIndex(int size, int mode) {
    if (mode == 0) return rnd.next(1, size);
    if (mode == 1) return rnd.any(vector<int>{1, size});
    if (mode == 2) return rnd.next(1, min(size, 4));
    if (mode == 3) return max(1, size - rnd.next(0, min(size - 1, 3)));

    int base = rnd.next(1, size);
    int delta = rnd.next(-2, 2);
    if (base + delta < 1) return 1;
    if (base + delta > size) return size;
    return base + delta;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 0;
    } else if (mode <= 3) {
        n = rnd.next(1, 5);
    } else if (mode == 4) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.any(vector<int>{13, 16, 20});
    }

    int q = (mode == 5 ? rnd.next(20, 80) : rnd.next(1, 30));
    int size = 1 << n;
    int indexMode = rnd.next(0, 4);
    int preferredType = rnd.next(0, 1);

    println(n, q);
    for (int i = 0; i < q; ++i) {
        int t;
        if (mode == 2) {
            t = i % 2;
        } else if (mode == 3) {
            t = preferredType;
        } else {
            t = rnd.next(0, 1);
        }

        int x;
        if (mode == 1 && i > 0 && rnd.next(0, 2) == 0) {
            x = rnd.any(vector<int>{1, size});
        } else {
            x = pickIndex(size, indexMode);
        }
        println(t, x);
    }

    return 0;
}
