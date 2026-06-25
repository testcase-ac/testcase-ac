#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int t = rnd.next(1, 20);
        for (int i = 0; i < t; ++i) values.push_back(rnd.next(1, 30));
    } else if (mode == 1) {
        int t = rnd.next(8, 35);
        int center = rnd.next(1, 200000);
        int radius = rnd.next(0, 50);
        for (int i = 0; i < t; ++i) {
            int lo = max(1, center - radius);
            int hi = min(200000, center + radius);
            values.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        int t = rnd.next(8, 30);
        for (int i = 0; i < t; ++i) {
            int base = rnd.any(vector<int>{1, 2, 3, 5, 7, 11, 16, 31, 32, 63, 64,
                                           97, 127, 128, 255, 256, 997, 1000,
                                           99991, 100000, 199999, 200000});
            int delta = rnd.next(-3, 3);
            values.push_back(min(200000, max(1, base + delta)));
        }
    } else if (mode == 3) {
        int t = rnd.next(20, 80);
        int a = rnd.next(1, 200000);
        int b = rnd.next(1, 200000);
        int c = rnd.next(1, 200000);
        for (int i = 0; i < t; ++i) values.push_back(rnd.any(vector<int>{a, b, c}));
    } else if (mode == 4) {
        int t = rnd.next(15, 60);
        int start = rnd.next(1, 199900);
        int step = rnd.next(1, 17);
        for (int i = 0; i < t; ++i) {
            long long candidate = start + 1LL * i * step;
            values.push_back((int)min(200000LL, candidate));
        }
        shuffle(values.begin(), values.end());
    } else {
        int t = rnd.next(20, 120);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 9) == 0) {
                values.push_back(rnd.any(vector<int>{1, 199999, 200000}));
            } else {
                values.push_back(rnd.next(1, 200000));
            }
        }
    }

    println((int)values.size());
    for (int n : values) println(n);

    return 0;
}
