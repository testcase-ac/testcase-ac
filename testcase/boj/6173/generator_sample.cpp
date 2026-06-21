#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 2 * rnd.next(1, 20);
    int c = rnd.next(2, min(n, 12));
    int pairs = n / 2;
    int mode = rnd.next(5);

    vector<int> count(c + 1, 0);

    if (mode == 0) {
        int a = rnd.next(1, c);
        int b = rnd.next(1, c - 1);
        if (b >= a) ++b;
        for (int i = 0; i < pairs; ++i) {
            ++count[a];
            ++count[b];
        }
    } else if (mode == 1) {
        int hub = rnd.next(1, c);
        vector<int> others;
        for (int color = 1; color <= c; ++color) {
            if (color != hub) others.push_back(color);
        }
        for (int i = 0; i < pairs; ++i) {
            ++count[hub];
            ++count[rnd.any(others)];
        }
    } else if (mode == 2) {
        vector<int> active;
        int activeSize = rnd.next(2, c);
        vector<int> colors;
        for (int color = 1; color <= c; ++color) colors.push_back(color);
        shuffle(colors.begin(), colors.end());
        for (int i = 0; i < activeSize; ++i) active.push_back(colors[i]);

        for (int i = 0; i < pairs; ++i) {
            int a = rnd.any(active);
            int b = rnd.any(active);
            while (a == b) b = rnd.any(active);
            ++count[a];
            ++count[b];
        }
    } else if (mode == 3) {
        for (int i = 0; i < pairs; ++i) {
            int a = (i % c) + 1;
            int b = ((i + 1 + rnd.next(0, c - 2)) % c) + 1;
            if (a == b) b = (b % c) + 1;
            ++count[a];
            ++count[b];
        }
    } else {
        for (int i = 0; i < pairs; ++i) {
            int a = rnd.next(1, min(c, 3));
            int b = rnd.next(1, c);
            while (a == b) b = rnd.next(1, c);
            ++count[a];
            ++count[b];
        }
    }

    println(n, c);
    for (int color = 1; color <= c; ++color) {
        println(count[color]);
    }

    return 0;
}
