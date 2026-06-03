#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int p;
    int n;
    vector<int> a;

    if (mode == 0) {
        p = 200;
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 200));
    } else if (mode == 1) {
        p = rnd.next(190, 199);
        n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 12));
    } else if (mode == 2) {
        p = rnd.next(1, 30);
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 4));
    } else if (mode == 3) {
        p = rnd.next(1, 199);
        n = rnd.next(5, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(100, 200));
            } else {
                a.push_back(rnd.next(1, 20));
            }
        }
    } else if (mode == 4) {
        p = rnd.next(160, 199);
        n = rnd.next(2, 30);
        int small = rnd.next(1, 5);
        int large = rnd.next(50, 200);
        for (int i = 0; i < n; ++i) a.push_back((i % 3 == 0) ? large : small);
    } else {
        p = rnd.next(1, 200);
        n = rnd.next(1, 60);
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, 200);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    shuffle(a.begin(), a.end());

    println(p, n);
    println(a);
    return 0;
}
