#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int upper = rnd.any(vector<int>{0, 1, 3, 7, 15, 31});
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, upper));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.next(0, 1000000000);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        int x = rnd.next(0, 1000000000);
        int y = rnd.next(0, 1000000000);
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? x : y);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        int bit = rnd.next(0, 29);
        int base = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int value = base ^ (1 << bit);
            if (rnd.next(0, 1)) value ^= rnd.next(0, 31);
            a.push_back(min(value, 1000000000));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 29);
            a.push_back(1 << bit);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 25);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(999999900, 1000000000));
    } else {
        n = rnd.next(10, 35);
        int upper = rnd.next(1000, 1000000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, upper));
        if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
