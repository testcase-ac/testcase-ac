#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int half;
    if (mode == 4) {
        half = rnd.next(2, 20);
    } else {
        half = rnd.next(2, 8);
    }

    int n = 2 * half;
    int l;
    if (mode == 3) {
        l = rnd.next(1, 40);
    } else {
        l = rnd.next(max(1, half - 1), 120);
    }
    int w = rnd.next(1, 20);

    vector<int> positions;
    positions.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            positions.push_back(rnd.next(0, l));
        }
    } else if (mode == 1) {
        int leftCluster = rnd.next(0, min(l, 5));
        int rightCluster = rnd.next(max(0, l - 5), l);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                positions.push_back(rnd.next(0, leftCluster));
            } else if (choice == 1) {
                positions.push_back(rnd.next(rightCluster, l));
            } else {
                positions.push_back(rnd.next(0, l));
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < half; ++i) {
            int ideal = half == 1 ? 0 : int((long long)l * i / (half - 1));
            int delta = rnd.next(-3, 3);
            positions.push_back(max(0, min(l, ideal + delta)));
            positions.push_back(max(0, min(l, ideal + rnd.next(-3, 3))));
        }
    } else if (mode == 3) {
        int a = rnd.next(0, l);
        int b = rnd.next(0, l);
        if (a > b) swap(a, b);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 4);
            if (choice == 0) {
                positions.push_back(0);
            } else if (choice == 1) {
                positions.push_back(l);
            } else {
                positions.push_back(rnd.next(a, b));
            }
        }
    } else {
        int span = rnd.next(1, min(l, 25));
        int center = rnd.next(0, l);
        for (int i = 0; i < n; ++i) {
            int lo = max(0, center - span);
            int hi = min(l, center + span);
            positions.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(positions.begin(), positions.end());

    println(n);
    println(l, w);
    for (int p : positions) {
        println(p);
    }

    return 0;
}
