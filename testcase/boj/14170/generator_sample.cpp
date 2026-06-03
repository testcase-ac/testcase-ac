#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 35);
    int q = rnd.next(1, 45);

    set<int> used;
    vector<int> positions;

    auto addPosition = [&](int x) {
        if (0 <= x && x <= 1000000000 && used.insert(x).second) {
            positions.push_back(x);
        }
    };

    if (mode == 0) {
        int start = rnd.next(0, 60);
        int step = rnd.next(1, 8);
        for (int i = 0; (int)positions.size() < n; ++i) {
            addPosition(start + i * step);
        }
    } else if (mode == 1) {
        int center = rnd.next(20, 200);
        while ((int)positions.size() < n) {
            addPosition(center + rnd.next(-20, 20));
        }
    } else if (mode == 2) {
        addPosition(0);
        addPosition(1000000000);
        while ((int)positions.size() < n) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) addPosition(rnd.next(0, 100));
            if (bucket == 1) addPosition(rnd.next(999999900, 1000000000));
            if (bucket == 2) addPosition(rnd.next(0, 1000000000));
        }
    } else {
        while ((int)positions.size() < n) {
            addPosition(rnd.next(0, 1000000000));
        }
    }

    shuffle(positions.begin(), positions.end());
    vector<int> sorted = positions;
    sort(sorted.begin(), sorted.end());

    println(n, q);
    println(positions);

    for (int i = 0; i < q; ++i) {
        int queryMode = rnd.next(0, 5);
        int a = 0;
        int b = 0;

        if (queryMode == 0) {
            int x = rnd.any(sorted);
            a = b = x;
        } else if (queryMode == 1) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            a = sorted[l];
            b = sorted[r];
        } else if (queryMode == 2) {
            int x = rnd.any(sorted);
            int delta = rnd.next(0, 20);
            a = max(0, x - delta);
            b = min(1000000000, x + rnd.next(0, 20));
        } else if (queryMode == 3) {
            a = rnd.next(0, 120);
            b = rnd.next(a, min(1000000000, a + rnd.next(0, 150)));
        } else if (queryMode == 4) {
            a = rnd.next(999999850, 1000000000);
            b = rnd.next(a, 1000000000);
        } else {
            int l = rnd.next(0, 1000000000);
            int span = rnd.next(0, 200000);
            a = l;
            b = min(1000000000, l + span);
        }

        println(a, b);
    }

    return 0;
}
