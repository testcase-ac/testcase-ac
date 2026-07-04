#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    vector<int> h;

    if (mode == 0) {
        n = rnd.next(1, 8);
        h.assign(n, 0);
        int bumps = rnd.next(0, n);
        for (int i = 0; i < bumps; ++i) {
            h[rnd.next(n)] += rnd.any(vector<int>{1, 2, 3});
        }
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        h.resize(n);
        for (int& x : h) x = rnd.next(0, 12);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        h.resize(n);
        for (int& x : h) x = 2 * rnd.next(0, 8);
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        h.resize(n);
        for (int& x : h) x = 2 * rnd.next(0, 7) + 1;
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        h.resize(n);
        int sum = 0;
        for (int& x : h) {
            x = rnd.next(0, 20);
            sum += x;
        }
        if (sum % 3 != 0) {
            int add = 3 - sum % 3;
            int idx = rnd.next(n);
            h[idx] = min(10000, h[idx] + add);
        }
    } else if (mode == 5) {
        n = rnd.next(1, 12);
        h.resize(n);
        int sum = 0;
        for (int& x : h) {
            x = rnd.next(0, 20);
            sum += x;
        }
        int idx = rnd.next(n);
        int targetRemainder = rnd.next(1, 2);
        int add = (targetRemainder - sum % 3 + 3) % 3;
        if (add == 0) add = 3;
        h[idx] = min(10000, h[idx] + add);
    } else if (mode == 6) {
        n = rnd.next(1, 20);
        h.resize(n);
        for (int& x : h) x = rnd.next(0, 100);
        h[rnd.next(n)] = rnd.any(vector<int>{0, 1, 2, 9999, 10000});
    } else {
        n = rnd.next(50, 300);
        h.resize(n);
        for (int& x : h) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) x = rnd.next(0, 10);
            else if (bucket == 1) x = rnd.next(9990, 10000);
            else x = rnd.next(0, 10000);
        }
    }

    shuffle(h.begin(), h.end());
    println(n);
    println(h);

    return 0;
}
