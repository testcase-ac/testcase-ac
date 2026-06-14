#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 2);
        a.assign(n, rnd.next(1, 100000));
    } else if (mode == 1) {
        n = rnd.next(3, 18);
        int lo = rnd.next(1, 99999);
        int hi = rnd.next(lo + 1, 100000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 1) ? lo : hi);
    } else if (mode == 2) {
        n = rnd.next(3, 24);
        int x = rnd.next(1, 99998);
        int y = rnd.next(x + 1, 99999);
        int z = rnd.next(y + 1, 100000);
        vector<int> values = {x, y, z};
        a = values;
        while ((int)a.size() < n) a.push_back(rnd.any(values));
    } else if (mode == 3) {
        n = rnd.next(8, 35);
        int kinds = rnd.next(3, 8);
        int base = rnd.next(1, 100000 - kinds + 1);
        for (int i = 0; i < n; ++i) {
            int step = rnd.wnext(kinds, -2);
            a.push_back(base + step);
        }
    } else if (mode == 4) {
        n = rnd.next(5, 30);
        int start = rnd.next(1, 100000 - n + 1);
        for (int i = 0; i < n; ++i) a.push_back(start + i);
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 5) {
        n = rnd.next(6, 28);
        vector<int> values = {1, 2, 99999, 100000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(values));
    } else {
        n = rnd.next(10, 40);
        int maxValue = rnd.next(3, 20);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, maxValue));
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    return 0;
}
