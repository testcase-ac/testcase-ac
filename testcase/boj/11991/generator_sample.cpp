#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> makeCoordinates(int limit, int count, int mode) {
    if (count == 0) {
        return {};
    }

    set<int> used;

    if (mode == 0) {
        while ((int)used.size() < count) {
            used.insert(rnd.next(1, limit - 1));
        }
    } else if (mode == 1) {
        int span = min(limit - 1, max(count, rnd.next(count, count + 20)));
        int start = rnd.next(1, limit - span);
        while ((int)used.size() < count) {
            used.insert(start + rnd.next(0, span - 1));
        }
    } else {
        int step = max(1, limit / (count + 1));
        for (int i = 1; i <= count; ++i) {
            int wiggle = max(1, step / 3);
            int x = i * step + rnd.next(-wiggle, wiggle);
            x = max(1, min(limit - 1, x));
            while (used.count(x)) {
                x = max(1, min(limit - 1, x + rnd.any(vector<int>{-1, 1})));
            }
            used.insert(x);
        }
    }

    vector<int> result(used.begin(), used.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int m = 0;
    int a = 0;
    int b = 0;

    if (mode == 0) {
        n = rnd.next(0, 2);
        m = rnd.next(0, 2);
        a = rnd.next(max(1, n + 1), 8);
        b = rnd.next(max(1, m + 1), 8);
    } else if (mode == 1) {
        n = rnd.next(1, 7);
        m = rnd.next(1, 7);
        a = rnd.next(n + 1, 30);
        b = rnd.next(m + 1, 30);
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        m = rnd.next(4, 14);
        a = rnd.next(n + 20, 120);
        b = rnd.next(m + 20, 120);
    } else if (mode == 3) {
        n = rnd.next(10, 35);
        m = rnd.next(1, 8);
        a = rnd.next(n + 50, 300);
        b = rnd.next(m + 10, 80);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        a = rnd.next(100000000, 1000000000);
        b = rnd.next(100000000, 1000000000);
    }

    int xMode = rnd.next(0, 2);
    int yMode = rnd.next(0, 2);
    vector<int> xs = makeCoordinates(a, n, xMode);
    vector<int> ys = makeCoordinates(b, m, yMode);

    println(a, b, n, m);
    for (int x : xs) {
        println(x);
    }
    for (int y : ys) {
        println(y);
    }

    return 0;
}
