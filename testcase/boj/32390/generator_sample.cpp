#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

static vector<int> makeComposition(int n, int m) {
    vector<int> parts(m, 1);
    int remaining = n - m;
    while (remaining > 0) {
        int i = rnd.next(m);
        int add = rnd.next(1, remaining);
        parts[i] += add;
        remaining -= add;
    }
    shuffle(parts.begin(), parts.end());
    return parts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 20);
        m = 1;
        a = {n};
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        m = n;
        a.assign(m, 1);
    } else if (mode == 2) {
        m = rnd.next(2, 12);
        int value = rnd.next(1, 8);
        n = m * value;
        a.assign(m, value);
    } else if (mode == 3) {
        n = rnd.next(5, 80);
        m = rnd.next(2, min(n, 12));
        a.assign(m, 1);
        a[rnd.next(m)] += n - m;
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(2, 120);
        m = rnd.next(1, min(n, 20));
        a = makeComposition(n, m);
    } else {
        n = rnd.next(30, 250);
        m = rnd.next(max(1, n / 3), n);
        a = makeComposition(n, m);
    }

    println(n, m);
    println(a);

    return 0;
}
