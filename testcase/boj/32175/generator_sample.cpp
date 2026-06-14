#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    int h = rnd.next(1, 200);
    vector<int> a;

    if (mode == 0) {
        n = 1;
        h = rnd.next(1, 100000);
        a.push_back(rnd.next(1, 100));
    } else if (mode == 1) {
        n = rnd.next(2, 100);
        h = rnd.next(1, 100000);
        int value = rnd.next(1, 100);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        h = rnd.next(1, 500);
        int maxValue = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, maxValue));
    } else if (mode == 3) {
        n = rnd.next(2, 60);
        h = rnd.next(1, 1000);
        int g = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(g * rnd.next(1, 100 / g));
        }
        if (rnd.next(0, 1)) h = g * rnd.next(1, 1000 / g);
    } else if (mode == 4) {
        n = rnd.next(50, 100);
        h = rnd.next(90000, 100000);
        int maxValue = rnd.next(10, 100);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, maxValue));
    } else if (mode == 5) {
        n = rnd.next(2, 100);
        h = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(90, 100));
    } else if (mode == 6) {
        n = rnd.next(1, 100);
        h = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) a.push_back((i % 100) + 1);
        shuffle(a.begin(), a.end());
    } else {
        n = rnd.next(2, 100);
        h = rnd.next(1, 100000);
        a.push_back(1);
        for (int i = 1; i < n; ++i) {
            int base = rnd.next(1, 12);
            a.push_back(min(100, base * rnd.next(1, 100 / base)));
        }
        shuffle(a.begin(), a.end());
    }

    println(n, h);
    println(a);

    return 0;
}
