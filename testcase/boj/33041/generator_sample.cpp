#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int h;
    vector<int> w;

    if (mode == 0) {
        h = 1;
        w.push_back(rnd.next(1, 20));
    } else if (mode == 1) {
        h = rnd.next(2, 10);
        w.assign(h, rnd.next(1, 8));
    } else if (mode == 2) {
        h = rnd.next(2, 12);
        int start = rnd.next(1, 5);
        for (int i = 0; i < h; ++i) w.push_back(start + i * rnd.next(0, 3));
    } else if (mode == 3) {
        h = rnd.next(2, 12);
        int cur = rnd.next(1, 20);
        for (int i = 0; i < h; ++i) {
            w.push_back(max(1, cur));
            cur -= rnd.next(0, 3);
        }
    } else if (mode == 4) {
        h = rnd.next(2, 12);
        for (int i = 0; i < h; ++i) w.push_back(i % 2 == 0 ? rnd.next(1, 3) : rnd.next(8, 18));
    } else if (mode == 5) {
        h = rnd.next(8, 18);
        for (int i = 0; i < h; ++i) w.push_back(rnd.next(1, 5));
    } else {
        h = rnd.next(2, 10);
        for (int i = 0; i < h; ++i) w.push_back(rnd.next(1, 25));
        shuffle(w.begin(), w.end());
    }

    int total = accumulate(w.begin(), w.end(), 0);
    int dMode = rnd.next(0, 5);
    int d;
    if (dMode == 0) {
        d = 0;
    } else if (dMode == 1) {
        d = total;
    } else if (dMode == 2) {
        d = rnd.next(0, min(total, h));
    } else if (dMode == 3) {
        d = total - rnd.next(0, min(total, h));
    } else if (dMode == 4) {
        d = total / 2 + rnd.next(-min(total / 2, 5), min((total + 1) / 2, 5));
    } else {
        d = rnd.next(0, total);
    }
    int c = total - d;

    println(h);
    println(w);
    println(c, d);

    return 0;
}
