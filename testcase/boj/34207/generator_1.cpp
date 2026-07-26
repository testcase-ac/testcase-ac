#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static pair<int, int> clampBox(long long s, long long c) {
    s = max(2LL, min(1000000000LL, s));
    c = max(1LL, min(999999999LL, c));
    if (c >= s) c = s - 1;
    return {(int)s, (int)c};
}

static void addBox(vector<pair<int, int>>& boxes, long long s, long long c) {
    boxes.push_back(clampBox(s, c));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    vector<pair<int, int>> boxes;

    if (mode == 0) {
        addBox(boxes, 2, 1);
        addBox(boxes, 1000000000, 999999999);
    } else if (mode == 1) {
        int n = rnd.next(2, 40);
        int start = rnd.next(2 * n + 5, 4 * n + 20);
        for (int i = 0; i < n; ++i) {
            int s = start - 2 * i;
            addBox(boxes, s, max(1, s - 2));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 80);
        int base = rnd.next(2, 100);
        for (int i = 0; i < n; ++i) {
            int c = base + i;
            addBox(boxes, c + 1, c);
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 90);
        int c = rnd.next(1, 40);
        int s = rnd.next(c + 1, c + 60);
        for (int i = 0; i < n; ++i) addBox(boxes, s, c);
    } else if (mode == 4) {
        int n = rnd.next(5, 120);
        for (int i = 0; i < n; ++i) {
            int c = rnd.next(1, 300);
            int width = rnd.next(1, 150);
            addBox(boxes, c + width, c);
        }
        shuffle(boxes.begin(), boxes.end());
    } else if (mode == 5) {
        int n = rnd.next(6, 100);
        int block = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int group = i % 5;
            int c = block + group * rnd.next(1, 5);
            int s = c + rnd.next(1, 25 - group);
            addBox(boxes, s, c);
        }
        shuffle(boxes.begin(), boxes.end());
    } else if (mode == 6) {
        int n = rnd.next(10, 160);
        long long base = 1000000000LL - rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            long long s = base - rnd.next(0, 5000);
            long long c = s - rnd.next(1, 5000);
            addBox(boxes, s, c);
        }
    } else if (mode == 7) {
        int n = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            int center = rnd.next(10, 500);
            int span = rnd.wnext(200, 3) + 1;
            addBox(boxes, center + span, max(1, center - rnd.next(0, 10)));
        }
        shuffle(boxes.begin(), boxes.end());
    } else {
        int n = rnd.next(2, 150);
        int current = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(0, 7);
            int c = rnd.next(1, current - 1);
            addBox(boxes, current, c);
        }
    }

    println((int)boxes.size());
    for (auto [s, c] : boxes) println(s, c);
    return 0;
}
