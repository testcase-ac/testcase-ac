#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static char gradeFor(int sum, int s, int g, int p, int d) {
    if (sum < s) return 'B';
    if (sum < g) return 'S';
    if (sum < p) return 'G';
    if (sum < d) return 'P';
    return 'D';
}

static int clampValue(int x, int lo, int hi) {
    return max(lo, min(hi, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 36);

    int s, g, p, d;
    if (mode == 0) {
        s = 1;
        g = 2;
        p = 3;
        d = rnd.next(4, 500);
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        d = rnd.next(4, 500);
        p = d - 1;
        g = p - 1;
        s = g - 1;
    } else if (mode == 2) {
        d = rnd.next(150, 500);
        s = rnd.next(1, d / 4);
        g = rnd.next(s + 1, d / 2);
        p = rnd.next(g + 1, d - 1);
    } else {
        vector<int> cuts;
        while ((int)cuts.size() < 4) {
            int x = rnd.next(1, 500);
            if (find(cuts.begin(), cuts.end(), x) == cuts.end()) cuts.push_back(x);
        }
        sort(cuts.begin(), cuts.end());
        s = cuts[0];
        g = cuts[1];
        p = cuts[2];
        d = cuts[3];
    }

    vector<int> focus = {0, d, s - 1, s, g - 1, g, p - 1, p, d - 1};
    for (int x = max(0, d / 2 - 2); x <= min(d, d / 2 + 2); ++x) {
        focus.push_back(x);
    }
    for (int& x : focus) x = clampValue(x, 0, d);

    vector<int> pay(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 3) {
            pay[i] = (i % 2 == 0 ? 0 : d);
        } else if (mode == 4) {
            int base = (i == 0 ? rnd.any(focus) : pay[i - 1]);
            pay[i] = clampValue(base + rnd.next(-3, 3), 0, d);
        } else if (mode == 5) {
            pay[i] = rnd.next(0, d);
        } else {
            pay[i] = rnd.any(focus);
        }
    }

    string grades;
    int previous = 0;
    for (int current : pay) {
        grades += gradeFor(previous + current, s, g, p, d);
        previous = current;
    }

    println(n);
    println(s, g, p, d);
    println(grades);

    return 0;
}
