#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_A = -268435456;
const int MAX_A = 268435456;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> good = {
        202021, 20202021, 202002021, 202012021, 202022021, 202032021,
        202042021, 202052021, 202062021, 202072021, 202082021, 202092021,
    };

    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(2, 24);
        vector<int> a;

        if (mode == 0) {
            int target = rnd.any(good);
            int pairs = rnd.next(1, min(8, n / 2));
            for (int i = 0; i < pairs; ++i) {
                int lo = max(MIN_A, target - MAX_A);
                int hi = min(MAX_A, target - MIN_A);
                int x = rnd.next(lo, hi);
                a.push_back(x);
                a.push_back(target - x);
            }
        } else if (mode == 1) {
            int target = rnd.any(good);
            int x = rnd.next(max(MIN_A, target - MAX_A), min(MAX_A, target - MIN_A));
            int y = target - x;
            int cx = rnd.next(1, min(10, n - 1));
            int cy = rnd.next(1, min(10, n - cx));
            a.insert(a.end(), cx, x);
            a.insert(a.end(), cy, y);
        } else if (mode == 2) {
            a.push_back(MIN_A);
            a.push_back(MAX_A);
            a.push_back(0);
            a.push_back(rnd.any(good));
            a.push_back(1);
            a.push_back(-1);
        } else {
            int lo = rnd.next(-1000000, 1000000);
            int hi = rnd.next(lo, min(MAX_A, lo + rnd.next(10, 5000000)));
            while ((int)a.size() < n) {
                a.push_back(rnd.next(max(MIN_A, lo), hi));
            }
        }

        while ((int)a.size() < n) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(MIN_A, MAX_A));
            } else {
                int target = rnd.any(good);
                int x = rnd.next(max(MIN_A, target - MAX_A), min(MAX_A, target - MIN_A));
                a.push_back(x);
            }
        }

        if ((int)a.size() > n) {
            shuffle(a.begin(), a.end());
            a.resize(n);
        }
        shuffle(a.begin(), a.end());

        println((int)a.size());
        println(a);
    }

    return 0;
}
