#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MIN_A = -1000000;
const int MAX_A = 1000000;

vector<int> randomCase(int n) {
    int lo = rnd.next(-20, 20);
    int hi = rnd.next(lo, lo + rnd.next(0, 30));
    vector<int> a(n);
    for (int& x : a) x = rnd.next(lo, hi);
    return a;
}

vector<int> monotoneCase(int n, bool increasing) {
    vector<int> a;
    int value = rnd.next(-1000, 1000);
    for (int i = 0; i < n; ++i) {
        value += rnd.next(1, 8);
        a.push_back(value);
    }
    if (!increasing) reverse(a.begin(), a.end());
    return a;
}

vector<int> duplicateBlocksCase(int n) {
    vector<int> a;
    int blocks = rnd.next(1, min(n, 8));
    int value = rnd.next(-50, 50);
    for (int block = 0; block < blocks; ++block) {
        value += rnd.next(0, 4);
        int remaining = n - (int)a.size();
        int take = block + 1 == blocks ? remaining : rnd.next(1, remaining - (blocks - block - 1));
        for (int i = 0; i < take; ++i) a.push_back(value);
    }
    if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    return a;
}

vector<int> sawCase(int n) {
    vector<int> a;
    int low = rnd.next(-100, -1);
    int high = rnd.next(1, 100);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            a.push_back(low + i / 2 + rnd.next(0, 2));
        } else {
            a.push_back(high - i / 2 - rnd.next(0, 2));
        }
    }
    return a;
}

vector<int> segmentedCase(int n) {
    vector<int> a;
    int segments = rnd.next(2, min(n, 7));
    int base = rnd.next(-500, 500);
    for (int seg = 0; seg < segments; ++seg) {
        int remaining = n - (int)a.size();
        int len = seg + 1 == segments ? remaining : rnd.next(1, remaining - (segments - seg - 1));
        int start = base + rnd.next(-20, 20);
        for (int i = 0; i < len; ++i) a.push_back(start + i * rnd.next(1, 4));
        base += rnd.next(-10, 10);
    }
    return a;
}

vector<int> boundaryCase(int n) {
    vector<int> choices = {MIN_A, MIN_A + 1, -1, 0, 1, MAX_A - 1, MAX_A};
    vector<int> a;
    for (int i = 0; i < n; ++i) a.push_back(rnd.any(choices));
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 6 ? tc : rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 8);
        } else if (mode == 1 || mode == 2) {
            n = rnd.next(2, 30);
        } else if (mode == 5) {
            n = rnd.next(8, 60);
        } else {
            n = rnd.next(4, 40);
        }

        vector<int> a;
        if (mode == 0) {
            a = randomCase(n);
        } else if (mode == 1) {
            a = monotoneCase(n, true);
        } else if (mode == 2) {
            a = monotoneCase(n, false);
        } else if (mode == 3) {
            a = duplicateBlocksCase(n);
        } else if (mode == 4) {
            a = sawCase(n);
        } else {
            a = rnd.next(0, 2) == 0 ? segmentedCase(n) : boundaryCase(n);
        }

        println(n);
        println(a);
    }

    return 0;
}
