#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int l;
    vector<int> g;

    if (mode == 0) {
        n = rnd.next(1, 12);
        l = 1;
        g.push_back(rnd.next(1, n));
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        l = rnd.next(1, n);
        vector<int> values;
        for (int x = 1; x <= n; ++x) values.push_back(x);
        shuffle(values.begin(), values.end());
        values.resize(l);
        sort(values.begin(), values.end());
        g = values;
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        l = n;
        for (int x = 1; x <= n; ++x) g.push_back(x);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        l = rnd.next(2, min(n, 8));
        vector<int> values;
        for (int x = 1; x < n; ++x) values.push_back(x);
        shuffle(values.begin(), values.end());
        values.resize(l - 1);
        sort(values.begin(), values.end());
        g = values;
        g.push_back(n);
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        l = rnd.next(1, min(n, 10));
        vector<int> values;
        for (int x = 1; x <= n; ++x) values.push_back(x);
        shuffle(values.begin(), values.end());
        values.resize(l);
        sort(values.begin(), values.end());
        g = values;
    } else {
        n = 1000000;
        l = rnd.next(1, 12);
        int cur = rnd.next(1, 20);
        g.push_back(cur);
        while ((int)g.size() < l) {
            int remaining = l - (int)g.size() - 1;
            int maxStep = max(1, (n - cur - remaining) / 3);
            cur += rnd.next(1, maxStep);
            g.push_back(cur);
        }
    }

    println(n, l);
    println(g);

    return 0;
}
