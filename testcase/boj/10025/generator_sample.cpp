#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    int k;
    vector<int> xs;

    if (mode == 0) {
        k = rnd.next(1, 6);
        int start = rnd.next(0, 30);
        int step = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) xs.push_back(start + i * step);
    } else if (mode == 1) {
        k = rnd.next(1, 20);
        set<int> used;
        while ((int)xs.size() < n) {
            int center = rnd.next(10, 80);
            int radius = rnd.next(0, 2 * k + 3);
            int x = max(0, center + rnd.next(-radius, radius));
            if (used.insert(x).second) xs.push_back(x);
        }
    } else if (mode == 2) {
        k = rnd.next(1, 12);
        n = rnd.next(1, min(18, 2 * (k + 1)));
        int left = rnd.next(0, 40);
        int gap = 2 * k + rnd.next(0, 4);
        set<int> used;
        while ((int)xs.size() < n) {
            int base = ((int)xs.size() % 2 == 0) ? left : left + gap;
            int x = base + rnd.next(0, max(1, k));
            if (used.insert(x).second) xs.push_back(x);
        }
    } else if (mode == 3) {
        k = rnd.next(500000, 2000000);
        set<int> used;
        vector<int> anchors = {0, 1, 500000, 999999, 1000000};
        shuffle(anchors.begin(), anchors.end());
        for (int x : anchors) {
            if ((int)xs.size() < n && used.insert(x).second) xs.push_back(x);
        }
        while ((int)xs.size() < n) {
            int x = rnd.next(0, 1000000);
            if (used.insert(x).second) xs.push_back(x);
        }
    } else {
        k = rnd.next(1, 100);
        set<int> used;
        while ((int)xs.size() < n) {
            int x = rnd.next(0, 250);
            if (used.insert(x).second) xs.push_back(x);
        }
    }

    shuffle(xs.begin(), xs.end());

    println(n, k);
    for (int x : xs) {
        int g;
        if (rnd.next(0, 4) == 0) {
            g = rnd.next(9000, 10000);
        } else {
            g = rnd.next(1, 80);
        }
        println(g, x);
    }

    return 0;
}
