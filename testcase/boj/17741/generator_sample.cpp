#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int pickValue(int mode) {
    if (mode == 0) return rnd.next(-20, 20);
    if (mode == 1) return rnd.next(0, 50);
    if (mode == 2) return -rnd.next(1, 50);
    if (mode == 3) return rnd.any(vector<int>{-1000000, -50, -1, 0, 1, 50, 1000000});
    return rnd.next(-1000, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<pair<int, int>> straps;

    if (mode == 0) {
        int valueMode = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, min(n, 4));
            straps.push_back({a, pickValue(valueMode)});
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int a = (i == 0 ? rnd.next(1, n) : rnd.next(0, 1));
            int b = (i == 0 ? rnd.next(-30, 10) : rnd.next(1, 80));
            straps.push_back({a, b});
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, min(n, 15));
            int b = rnd.next(-80, -1);
            straps.push_back({a, b});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, n);
            int b = rnd.any(vector<int>{-1000000, -999999, -1, 0, 1, 999999, 1000000});
            straps.push_back({a, b});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, min(n, 2));
            int b = (i % 3 == 0 ? rnd.next(-100, -1) : rnd.next(1, 100));
            straps.push_back({a, b});
        }
    } else {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, n);
            int b = rnd.next(-1000, 1000);
            straps.push_back({a, b});
        }
    }

    shuffle(straps.begin(), straps.end());

    println(n);
    for (const auto& strap : straps) {
        println(strap.first, strap.second);
    }

    return 0;
}
