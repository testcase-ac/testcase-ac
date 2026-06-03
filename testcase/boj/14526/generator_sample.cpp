#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> makeNested(int n, int depth) {
    vector<int> a(n, 0);
    int left = 0;
    int right = n - 1;
    int color = 1;
    while (left <= right && color <= depth) {
        a[left++] = color;
        if (left <= right) a[right--] = color;
        ++color;
    }
    for (int i = left; i <= right; ++i) {
        if (rnd.next(3) != 0) a[i] = rnd.next(1, max(1, depth));
    }
    return a;
}

static vector<int> makeDisjoint(int n) {
    vector<int> a(n, 0);
    int color = 1;
    for (int i = 0; i < n;) {
        if (rnd.next(4) == 0) {
            ++i;
            continue;
        }
        int len = rnd.next(1, min(4, n - i));
        for (int j = 0; j < len; ++j) a[i + j] = color;
        ++color;
        i += len;
    }
    return a;
}

static vector<int> makeCrossing(int n) {
    vector<int> a(n, 0);
    int leftPad = rnd.next(0, max(0, n - 4));
    a[leftPad] = 1;
    a[leftPad + 1] = 2;
    a[leftPad + 2] = 1;
    a[leftPad + 3] = 2;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0 && rnd.next(5) == 0) a[i] = rnd.next(3, n);
    }
    return a;
}

static vector<int> makeRandomPainting(int n) {
    vector<int> a(n);
    int maxColor = rnd.next(0, n);
    for (int i = 0; i < n; ++i) a[i] = rnd.next(0, maxColor);
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        a.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 25);
        int depth = rnd.next(1, n);
        a = makeNested(n, depth);
    } else if (mode == 2) {
        n = rnd.next(1, 35);
        a = makeDisjoint(n);
    } else if (mode == 3) {
        n = rnd.next(4, 35);
        a = makeCrossing(n);
    } else if (mode == 4) {
        n = rnd.next(2, 45);
        a = makeRandomPainting(n);
    } else {
        n = rnd.next(40, 120);
        int depth = rnd.next(1, min(n, 20));
        a = makeNested(n, depth);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(10) == 0) a[i] = 0;
        }
    }

    println(n);
    for (int color : a) println(color);

    return 0;
}
