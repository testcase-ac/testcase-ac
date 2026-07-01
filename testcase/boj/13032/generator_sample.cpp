#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomPower(int mode, const vector<int>& xs, int i) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.next(1, 1000000);
    if (mode == 2 && i > 0) {
        int span = xs[i] - xs[rnd.next(0, i - 1)];
        return max(1, span + rnd.next(-2, 6));
    }
    if (mode == 3) return rnd.next(1, min(1000000, xs[i] + 10));
    return rnd.next(1, 40);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = (mode == 0) ? 1 : rnd.next(2, 24);
    vector<int> xs;

    if (mode == 1) {
        int start = rnd.next(0, 1000000 - n + 1);
        for (int i = 0; i < n; ++i) xs.push_back(start + i);
    } else if (mode == 2) {
        int x = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, 4);
            xs.push_back(x);
        }
    } else if (mode == 3) {
        int x = rnd.next(0, 200000);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, 50000);
            if (x > 1000000) break;
            xs.push_back(x);
        }
        n = (int)xs.size();
    } else if (mode == 4) {
        xs.push_back(0);
        while ((int)xs.size() < n - 1) xs.push_back(rnd.next(1, 999999));
        xs.push_back(1000000);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = (int)xs.size();
    } else {
        xs.push_back(rnd.next(0, 1000000));
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(xs[i], randomPower(mode, xs, i));
    }

    return 0;
}
