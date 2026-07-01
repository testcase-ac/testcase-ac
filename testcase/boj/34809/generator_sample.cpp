#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        a.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 50));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        int lo = rnd.next(999900, 1000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, 1000000));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        int value = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(rnd.next(0, 1000000));
            } else {
                a.push_back(value);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 35);
        int start = rnd.next(0, 1000000 - n + 1);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i);
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else {
        n = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                a.push_back(rnd.next(0, 20));
            } else if (bucket == 1) {
                a.push_back(rnd.next(999980, 1000000));
            } else if (bucket == 2) {
                a.push_back(rnd.next(0, 1000) * 1000);
            } else {
                a.push_back(rnd.next(0, 1000000));
            }
        }
    }

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
