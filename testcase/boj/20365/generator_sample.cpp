#include "testlib.h"
#include <string>
using namespace std;

static char other(char c) {
    return c == 'R' ? 'B' : 'R';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    string colors;

    if (mode == 0) {
        n = rnd.next(1, 12);
        colors.assign(n, rnd.next(0, 1) ? 'R' : 'B');
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        char cur = rnd.next(0, 1) ? 'R' : 'B';
        for (int i = 0; i < n; ++i) {
            colors += cur;
            cur = other(cur);
        }
    } else if (mode == 2) {
        int runs = rnd.next(2, 12);
        char cur = rnd.next(0, 1) ? 'R' : 'B';
        for (int i = 0; i < runs; ++i) {
            int len = rnd.next(1, 6);
            colors.append(len, cur);
            cur = other(cur);
        }
        n = (int)colors.size();
    } else if (mode == 3) {
        n = rnd.next(3, 40);
        char dominant = rnd.next(0, 1) ? 'R' : 'B';
        colors.assign(n, dominant);
        int changes = rnd.next(1, min(n, 8));
        for (int i = 0; i < changes; ++i) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            for (int j = l; j <= r; ++j) colors[j] = other(dominant);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        char cur = rnd.next(0, 1) ? 'R' : 'B';
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 99) < 35) cur = other(cur);
            colors += cur;
        }
    } else {
        n = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) {
            colors += rnd.next(0, 99) < 70 ? 'R' : 'B';
        }
        if (rnd.next(0, 1)) {
            for (char& c : colors) c = other(c);
        }
    }

    println(n);
    println(colors);

    return 0;
}
