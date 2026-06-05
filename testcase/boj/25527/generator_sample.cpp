#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_V = 1000;

void fixAdjacent(vector<int>& v) {
    v[0] = 0;
    for (int i = 1; i < int(v.size()); ++i) {
        if (v[i] == v[i - 1]) {
            if (v[i] < MAX_V) {
                ++v[i];
            } else {
                --v[i];
            }
        }
    }
}

vector<int> increasingCase(int n) {
    vector<int> v(n);
    v[0] = 0;
    int cur = 0;
    for (int i = 1; i < n; ++i) {
        int remaining = n - 1 - i;
        int step = rnd.next(1, max(1, (MAX_V - cur - remaining) / max(1, remaining + 1)));
        cur = min(MAX_V - remaining, cur + step);
        v[i] = cur;
    }
    fixAdjacent(v);
    return v;
}

vector<int> decreasingTailCase(int n) {
    vector<int> v(n);
    v[0] = 0;
    v[1] = rnd.next(1, MAX_V);
    for (int i = 2; i < n; ++i) {
        v[i] = max(0, v[i - 1] - rnd.next(1, max(1, v[i - 1])));
    }
    fixAdjacent(v);
    return v;
}

vector<int> alternatingCase(int n) {
    vector<int> v(n);
    v[0] = 0;
    int lowMax = rnd.next(0, 30);
    int highMin = rnd.next(700, 970);
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 1) {
            v[i] = rnd.next(highMin, MAX_V);
        } else {
            v[i] = rnd.next(0, lowMax);
        }
    }
    fixAdjacent(v);
    return v;
}

vector<int> boundedWalkCase(int n) {
    vector<int> v(n);
    v[0] = 0;
    int cur = rnd.next(1, MAX_V);
    for (int i = 1; i < n; ++i) {
        int span = rnd.next(1, 180);
        if (rnd.next(2) == 0) {
            cur = max(0, cur - span);
        } else {
            cur = min(MAX_V, cur + span);
        }
        v[i] = cur;
    }
    fixAdjacent(v);
    return v;
}

vector<int> sparsePeakCase(int n) {
    vector<int> v(n);
    v[0] = 0;
    int base = rnd.next(0, 20);
    for (int i = 1; i < n; ++i) {
        v[i] = base + rnd.next(0, 8);
    }
    for (int i = 2; i + 1 < n; i += rnd.next(3, 6)) {
        v[i] = rnd.next(500, MAX_V);
    }
    fixAdjacent(v);
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(8, 20);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = rnd.next(5);
        int n;
        if (tc < 3) {
            n = 3 + tc;
        } else if (mode == 3) {
            n = rnd.next(20, 80);
        } else {
            n = rnd.next(3, 25);
        }

        vector<int> v;
        if (mode == 0) {
            v = increasingCase(n);
        } else if (mode == 1) {
            v = decreasingTailCase(n);
        } else if (mode == 2) {
            v = alternatingCase(n);
        } else if (mode == 3) {
            v = boundedWalkCase(n);
        } else {
            v = sparsePeakCase(n);
        }

        println(n);
        println(v);
    }
    println(0);
}
