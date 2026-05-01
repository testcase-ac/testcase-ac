#include "testlib.h"
using namespace std;

bool hitsGround(int h, int M, int &firstT) {
    firstT = -1;
    for (int t = 1; t <= M; ++t) {
        long long tt = t;
        long long t2 = tt * tt;
        long long t3 = t2 * tt;
        long long t4 = t2 * t2;
        long long A = -6 * t4 + (long long)h * t3 + 2 * t2 + tt;
        if (A <= 0) {
            firstT = t;
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h = 0, M = 1;

    int pattern = rnd.next(0, 4); // choose one of several patterns

    switch (pattern) {
        case 0: { // fairly random
            if (rnd.next(0, 1) == 0)
                M = rnd.next(1, 20);
            else
                M = rnd.next(1, 239);
            h = rnd.next(0, 100);
            break;
        }
        case 1: { // guaranteed very early hit (often at t = 1)
            bool ok = false;
            for (int it = 0; it < 1000 && !ok; ++it) {
                M = rnd.next(3, 20);
                h = rnd.next(0, 100);
                int firstT;
                if (hitsGround(h, M, firstT) && firstT <= 3)
                    ok = true;
            }
            if (!ok) {
                // ensure hit at t = 1 (A(1) = h - 3 <= 0)
                h = rnd.next(0, 3);
                M = rnd.next(1, 20);
            }
            break;
        }
        case 2: { // hit close to the maximum time M
            bool ok = false;
            for (int it = 0; it < 3000 && !ok; ++it) {
                M = rnd.next(5, 30);
                h = rnd.next(0, 100);
                int firstT;
                if (hitsGround(h, M, firstT) && firstT >= M - 2)
                    ok = true;
            }
            if (!ok) {
                // fallback to known "hit" case (not necessarily late)
                h = 30;
                M = 10;
            }
            break;
        }
        case 3: { // guaranteed no touch within M
            bool ok = false;
            for (int it = 0; it < 2000 && !ok; ++it) {
                M = rnd.next(5, 20);
                h = rnd.next(0, 100);
                int firstT;
                if (!hitsGround(h, M, firstT))
                    ok = true;
            }
            if (!ok) {
                // fallback to known "no hit" sample
                h = 70;
                M = 10;
            }
            break;
        }
        case 4: { // large M near upper bound
            M = rnd.next(100, 239);
            if (rnd.next(0, 2) == 0)
                h = rnd.any(vector<int>{0, 100});
            else
                h = rnd.next(0, 100);
            break;
        }
    }

    println(h);
    println(M);

    return 0;
}
