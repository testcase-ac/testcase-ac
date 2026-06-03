#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char gradeFor(int sum, int s, int g, int p, int d) {
    if (sum < s) return 'B';
    if (sum < g) return 'S';
    if (sum < p) return 'G';
    if (sum < d) return 'P';
    return 'D';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int s = 1, g = 2, p = 3, d = 4;

    if (mode == 0) {
        n = rnd.next(1, 6);
        s = rnd.next(1, 8);
        g = rnd.next(s + 1, s + 8);
        p = rnd.next(g + 1, g + 8);
        d = rnd.next(p + 1, p + 12);
    } else if (mode == 1) {
        n = rnd.next(20, 36);
        s = rnd.next(1, 40);
        g = s + rnd.next(1, 5);
        p = g + rnd.next(1, 5);
        d = p + rnd.next(1, 6);
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        s = rnd.next(100, 5000);
        g = rnd.next(s + 1, min(20000, s + 5000));
        p = rnd.next(g + 1, min(35000, g + 7000));
        d = rnd.next(p + 1, 50000);
    } else if (mode == 3) {
        n = rnd.next(24, 36);
        d = rnd.next(49960, 50000);
        p = rnd.next(max(3, d - 30), d - 1);
        g = rnd.next(max(2, p - 30), p - 1);
        s = rnd.next(max(1, g - 30), g - 1);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        s = rnd.next(1, 120);
        g = rnd.next(s + 1, s + 120);
        p = rnd.next(g + 1, g + 120);
        d = rnd.next(p + 1, p + 120);
    } else {
        n = rnd.next(30, 36);
        s = rnd.next(1, 10000);
        g = rnd.next(s + 1, 25000);
        p = rnd.next(g + 1, 40000);
        d = rnd.next(p + 1, 50000);
    }

    vector<int> paid(n);
    if (mode == 4) {
        vector<int> focus = {0, max(0, s - 1), s, max(0, g - s), g, max(0, p - g),
                             p, max(0, d - p), d};
        for (int i = 0; i < n; ++i) {
            paid[i] = min(d, rnd.any(focus) + rnd.next(-1, 1));
            paid[i] = max(0, min(d, paid[i]));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int shape = rnd.next(0, 4);
            if (shape == 0) {
                paid[i] = rnd.next(0, min(d, max(1, s)));
            } else if (shape == 1) {
                paid[i] = rnd.next(0, d);
            } else if (shape == 2) {
                paid[i] = rnd.wnext(d + 1, 2);
            } else if (shape == 3) {
                paid[i] = rnd.wnext(d + 1, -2);
            } else {
                paid[i] = rnd.next(max(0, d - 5), d);
            }
        }
    }

    if (mode == 1) {
        for (int i = 0; i < n; i += rnd.next(2, 5)) {
            paid[i] = rnd.next(0, min(d, s));
        }
    }

    string grades;
    grades.reserve(n);
    for (int i = 0; i < n; ++i) {
        int previous = (i == 0 ? 0 : paid[i - 1]);
        grades.push_back(gradeFor(previous + paid[i], s, g, p, d));
    }

    println(n);
    println(s, g, p, d);
    println(grades);

    return 0;
}
