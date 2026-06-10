#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a = {1};
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        int value = rnd.next(1, n);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        int limit = rnd.next(1, min(n, 5));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, limit));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 45);
        int peak = rnd.next(max(1, n / 2), n);
        int copies = rnd.next(2, min(n, 12));
        for (int i = 0; i < copies; ++i) {
            a.push_back(peak);
        }
        while ((int)a.size() < n) {
            a.push_back(rnd.next(1, n));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 25);
        for (int i = 1; i <= n; ++i) {
            a.push_back(i);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 50);
        int low = rnd.next(1, n);
        int high = rnd.next(low, n);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(low, high));
        }
    } else if (mode == 6) {
        n = rnd.next(8, 80);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(1, min(n, 10));
            if (rnd.next(0, 3) == 0) {
                value = rnd.next(1, n);
            }
            a.push_back(value);
        }
    } else {
        n = rnd.next(2, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, n));
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
