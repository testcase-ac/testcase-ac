#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int k;
    vector<int> buildings;

    if (mode == 0) {
        n = rnd.next(1, 30);
        m = 1;
        k = rnd.next(1, 500);
        buildings.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        m = rnd.next(2, 6);
        k = rnd.next(1, min(500, n + 10));
        int step = rnd.next(1, m - 1);
        int cur = rnd.next(1, m);
        for (int i = 0; i < n; ++i) {
            buildings.push_back(cur);
            cur = (cur + step - 1) % m + 1;
        }
    } else if (mode == 2) {
        n = rnd.next(5, 60);
        m = rnd.next(2, 10);
        k = rnd.next(1, min(500, n + 20));
        int hot = rnd.next(1, m);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                buildings.push_back(hot);
            } else {
                buildings.push_back(rnd.next(1, m));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(8, 70);
        m = rnd.next(2, 12);
        k = rnd.next(1, min(500, n + 30));
        while ((int)buildings.size() < n) {
            int label = rnd.next(1, m);
            int len = rnd.next(1, 8);
            for (int i = 0; i < len && (int)buildings.size() < n; ++i) {
                buildings.push_back(label);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(1, 45);
        m = rnd.next(20, 100);
        k = rnd.next(1, 500);
        int active = rnd.next(1, min(m, 8));
        vector<int> labels;
        for (int i = 1; i <= m; ++i) labels.push_back(i);
        shuffle(labels.begin(), labels.end());
        labels.resize(active);
        sort(labels.begin(), labels.end());
        for (int i = 0; i < n; ++i) {
            buildings.push_back(rnd.any(labels));
        }
    } else {
        n = rnd.next(80, 180);
        m = rnd.next(1, 20);
        k = rnd.next(1, 500);
        int cap = rnd.next(1, m);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 99) < 45) {
                buildings.push_back(buildings.back());
            } else {
                buildings.push_back(rnd.next(1, cap));
            }
        }
    }

    println(n, m, k);
    for (int building : buildings) {
        println(building);
    }

    return 0;
}
