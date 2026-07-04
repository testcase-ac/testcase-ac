#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int c;
    int n;
    vector<int> colors;

    if (mode == 0) {
        c = 1;
        n = rnd.next(1, 20);
        colors.assign(n, 1);
    } else if (mode == 1) {
        c = rnd.next(2, 20);
        n = c;
        colors.resize(n);
        for (int i = 0; i < c; ++i) {
            colors[i] = i + 1;
        }
        shuffle(colors.begin(), colors.end());
    } else {
        c = rnd.next(2, 12);
        n = rnd.next(c, 40);
        colors.resize(n);

        if (mode == 2) {
            vector<int> order(c);
            for (int i = 0; i < c; ++i) {
                order[i] = i + 1;
            }
            shuffle(order.begin(), order.end());

            int remaining = n;
            int pos = 0;
            for (int i = 0; i < c; ++i) {
                int maxRun = remaining - (c - i - 1);
                int run = (i + 1 == c) ? maxRun : rnd.next(1, maxRun);
                for (int j = 0; j < run; ++j) {
                    colors[pos + j] = order[i];
                }
                pos += run;
                remaining -= run;
            }
        } else {
            for (int i = 0; i < c; ++i) {
                colors[i] = i + 1;
            }
            int hotColor = rnd.next(1, c);
            int maxColor = rnd.next(1, c);
            for (int i = c; i < n; ++i) {
                if (mode == 3 && rnd.next(0, 99) < 65) {
                    colors[i] = hotColor;
                } else {
                    colors[i] = rnd.next(1, maxColor);
                }
            }
            shuffle(colors.begin(), colors.end());
        }
    }

    println(n, c);
    println(colors);
    return 0;
}
