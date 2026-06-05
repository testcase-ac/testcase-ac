#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

constexpr int MAX_VALUE = 500000;

int clampValue(int x) {
    return max(1, min(MAX_VALUE, x));
}

int nearValue(int base, int radius) {
    int lo = max(1, base - radius);
    int hi = min(MAX_VALUE, base + radius);
    return rnd.next(lo, hi);
}

int sameResidueValue(int residue, int k) {
    int first = residue == 0 ? k : residue;
    int count = (MAX_VALUE - first) / k + 1;
    return first + rnd.next(0, count - 1) * k;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    if (rnd.next(100) < 10) n = rnd.next(36, 90);

    int k;
    int d;
    if (rnd.next(100) < 20) {
        k = rnd.any(vector<int>{1, 2, 3, 499999, MAX_VALUE});
    } else {
        k = rnd.next(1, 200);
    }
    if (rnd.next(100) < 20) {
        d = rnd.any(vector<int>{1, 2, 3, 499999, MAX_VALUE});
    } else {
        d = rnd.next(1, 200);
    }

    vector<int> s;
    s.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(1, MAX_VALUE));
    } else if (mode == 1) {
        int residue = rnd.next(0, k - 1);
        for (int i = 0; i < n; ++i) s.push_back(sameResidueValue(residue, k));
    } else if (mode == 2) {
        int x = rnd.next(1, MAX_VALUE);
        for (int i = 0; i < n; ++i) {
            s.push_back(x);
            int step = rnd.next(-d, d);
            x = clampValue(x + step);
        }
    } else if (mode == 3) {
        int center = rnd.next(1, MAX_VALUE);
        int radius = min(d, rnd.next(1, 50));
        for (int i = 0; i < n; ++i) s.push_back(nearValue(center, radius));
    } else if (mode == 4) {
        vector<int> anchors = {1, 2, MAX_VALUE - 1, MAX_VALUE};
        for (int i = 0; i < n; ++i) {
            int anchor = rnd.any(anchors);
            s.push_back(nearValue(anchor, min(d, 5)));
        }
    } else {
        int residue = rnd.next(0, k - 1);
        int center = rnd.next(1, MAX_VALUE);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                s.push_back(sameResidueValue(residue, k));
            } else if (choice == 1) {
                s.push_back(nearValue(center, min(d, 30)));
            } else {
                s.push_back(rnd.next(1, MAX_VALUE));
            }
        }
    }

    if (rnd.next(100) < 30) shuffle(s.begin(), s.end());

    println(n, k, d);
    println(s);

    return 0;
}
