#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 45 : 14);
    vector<long long> x(n), len(n);
    vector<string> color(n);
    const vector<string> colors = {"R", "Y", "B"};

    if (mode == 0) {
        long long cur = rnd.next(-30, 10);
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            len[i] = rnd.next(1, 10);
            color[i] = colors[rnd.next(0, 2)];
            cur += rnd.next(1, 8);
        }
        int i = rnd.next(0, n - 2);
        len[i] = rnd.next(1, 6);
        len[i + 1] = x[i + 1] - x[i] - len[i];
        if (len[i + 1] < 1) len[i + 1] = 1;
        color[i] = "R";
        color[i + 1] = rnd.any(vector<string>{"Y", "B"});
    } else if (mode == 1) {
        long long cur = rnd.next(-40, -10);
        string c = colors[rnd.next(0, 2)];
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            len[i] = rnd.next(5, 20);
            color[i] = c;
            cur += rnd.next(1, 8);
        }
    } else if (mode == 2) {
        long long cur = rnd.next(-60, -20);
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            len[i] = rnd.next(1, 4);
            color[i] = colors[(i + rnd.next(0, 2)) % 3];
            cur += len[i] + rnd.next(4, 12);
        }
    } else if (mode == 3) {
        x[0] = rnd.next(-100, -20);
        len[0] = rnd.next(1, 15);
        color[0] = "B";
        for (int i = 1; i < n; ++i) {
            len[i] = rnd.next(1, 15);
            long long gap = len[i - 1] + len[i] + (rnd.next(0, 1) == 0 ? 0 : 1);
            x[i] = x[i - 1] + gap;
            color[i] = colors[i % 3];
        }
    } else if (mode == 4) {
        long long cur = -1000000000LL;
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            len[i] = rnd.next(1, 1000000000);
            color[i] = colors[rnd.next(0, 2)];
            long long remaining = 1000000000LL - cur;
            long long minStep = max(1LL, remaining / max(1, n - i));
            cur += rnd.next(minStep, minStep + 1000);
            if (cur > 1000000000LL - (n - i - 1)) cur = 1000000000LL - (n - i - 1);
        }
        color[0] = "R";
        color[n - 1] = "Y";
    } else {
        long long cur = rnd.next(-200, -100);
        long long baseLen = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            len[i] = max(1LL, baseLen + rnd.next(-3, 3));
            color[i] = colors[(i / rnd.next(1, 4)) % 3];
            cur += rnd.next(1, 2 * (int)baseLen + 3);
        }
    }

    println(n);
    println(x);
    println(len);
    println(color);

    return 0;
}
