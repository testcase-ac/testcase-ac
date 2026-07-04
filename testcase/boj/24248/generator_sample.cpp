#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Musician {
    int s;
    int e;
    int a;
};

int randomAttention(int mode) {
    if (mode == 0) return rnd.next(0, 20);
    if (mode == 1) return rnd.next(0, 1000000);
    if (mode == 2) return rnd.next(0, 1) ? rnd.next(1, 1000) : 0;
    return rnd.next(0, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    vector<Musician> musicians;
    musicians.reserve(n);

    if (mode == 0) {
        int t = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 8);
            int gap = rnd.next(0, 4);
            musicians.push_back({t, t + len, randomAttention(i % 4)});
            t += len + gap;
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            int s = base + rnd.next(0, 12);
            int e = s + rnd.next(1, 15);
            musicians.push_back({s, e, randomAttention(i % 4)});
        }
    } else if (mode == 2) {
        int left = rnd.next(0, 20);
        int right = left + rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int margin = rnd.next(0, max(0, (right - left) / 2 - 1));
            int s = left + margin;
            int e = right - rnd.next(0, margin);
            if (s >= e) e = s + 1;
            musicians.push_back({s, e, randomAttention(i % 4)});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int s;
            if (rnd.next(0, 3) == 0) {
                s = rnd.next(999980, 999999);
            } else if (rnd.next(0, 2) == 0) {
                s = 0;
            } else {
                s = rnd.next(0, 100);
            }
            int e = rnd.next(s + 1, 1000000);
            musicians.push_back({s, e, randomAttention(i % 4)});
        }
    } else if (mode == 4) {
        int coordinateMax = rnd.next(2, 120);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(0, coordinateMax - 1);
            int e = rnd.next(s + 1, coordinateMax);
            musicians.push_back({s, e, randomAttention(i % 4)});
        }
    } else {
        n = rnd.next(25, 70);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(0, 1000000 - 1);
            int e = rnd.next(s + 1, 1000000);
            musicians.push_back({s, e, randomAttention(i % 4)});
        }
    }

    shuffle(musicians.begin(), musicians.end());

    println(static_cast<int>(musicians.size()));
    for (const Musician& musician : musicians) {
        println(musician.s, musician.e, musician.a);
    }

    return 0;
}
