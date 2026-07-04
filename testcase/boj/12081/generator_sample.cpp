#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int s;
        int r;
        int c;

        if (mode == 0) {
            s = rnd.next(1, 8);
            r = rnd.next(1, 5);
            c = rnd.next(1, 5);
        } else if (mode == 1) {
            s = rnd.next(1, 12);
            r = rnd.next(1, 2);
            c = rnd.next(1, 20);
        } else if (mode == 2) {
            s = rnd.next(1, 12);
            r = rnd.next(1, 20);
            c = rnd.next(1, 2);
        } else if (mode == 3) {
            s = rnd.next(3, 25);
            r = rnd.next(2, 12);
            c = rnd.next(2, 12);
        } else if (mode == 4) {
            s = rnd.next(1, 15);
            r = rnd.next(99990, 100000);
            c = rnd.next(1, 8);
        } else {
            s = rnd.next(1, 15);
            r = rnd.next(1, 8);
            c = rnd.next(99990, 100000);
        }

        vector<int> times;
        int current = rnd.next(1, 6);
        for (int i = 0; i < s; ++i) {
            times.push_back(current);

            int remaining = s - i - 1;
            int maxStep = 1000000 - current - remaining;
            int step;
            if (mode >= 4) {
                int high = min(100000, maxStep);
                int low = max(1, high - 1000);
                step = rnd.next(low, high);
            } else if (rnd.next(0, 4) == 0) {
                step = rnd.next(10, 1000);
            } else {
                step = rnd.next(1, 9);
            }
            current += step;
        }

        if (rnd.next(0, 5) == 0) {
            int shift = 1000000 - times.back();
            int add = rnd.next(max(0, shift - 20), shift);
            for (int& time : times) {
                time += add;
            }
        }

        println(s, r, c);
        for (int i = 0; i < s; ++i) {
            string action;
            if (mode == 0) {
                action = (i % 2 == 0 ? "L" : "R");
            } else if (mode == 1) {
                action = (rnd.next(0, 3) == 0 ? "R" : "L");
            } else if (mode == 2) {
                action = (rnd.next(0, 3) == 0 ? "L" : "R");
            } else {
                action = (rnd.next(0, 1) == 0 ? "L" : "R");
            }
            println(times[i], action);
        }
    }

    return 0;
}
