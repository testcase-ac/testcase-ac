#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeSequence(int n, int mode) {
    vector<int> a(n, 0);

    if (mode == 0) {
        return a;
    }
    if (mode == 1) {
        fill(a.begin(), a.end(), 1);
        return a;
    }
    if (mode == 2) {
        int ones = rnd.next(0, min(n, 3));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < ones; ++i) a[pos[i]] = 1;
        return a;
    }
    if (mode == 3) {
        int zeros = rnd.next(0, min(n, 3));
        fill(a.begin(), a.end(), 1);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < zeros; ++i) a[pos[i]] = 0;
        return a;
    }

    double oneProb = rnd.next(0.15, 0.85);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next() < oneProb;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode <= 1) {
            n = rnd.next(1, 4);
        } else if (mode <= 3) {
            n = rnd.next(2, 12);
        } else {
            n = rnd.next(1, 30);
        }

        int k;
        if (tc < 3) {
            k = rnd.next(1, 12);
        } else if (rnd.next(0, 3) == 0) {
            k = rnd.next(900, 1000);
        } else {
            k = rnd.next(1, 80);
        }

        vector<int> sequence = makeSequence(n, mode);
        println(n, k);
        for (int bit : sequence) {
            println(bit);
        }
    }

    return 0;
}
