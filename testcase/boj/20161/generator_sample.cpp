#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

void applyOperation(vector<int>& state, int left, int k, int skipped) {
    for (int i = 0; i < k; ++i) {
        if (i != skipped) state[left + i] ^= 1;
    }
}

vector<int> randomBits(int n) {
    vector<int> bits(n);
    for (int i = 0; i < n; ++i) bits[i] = rnd.next(0, 1);
    return bits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(10, 25);
        k = 10;
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        k = rnd.next(2, min(10, n));
    } else if (mode == 5) {
        n = rnd.next(20, 45);
        k = rnd.next(2, min(10, n));
    } else if (mode == 6) {
        n = rnd.next(90, 100);
        k = rnd.next(1, 10);
    } else {
        n = rnd.next(1, 35);
        k = rnd.next(1, min(10, n));
    }

    vector<int> current = randomBits(n);
    vector<int> target = current;

    if (mode == 0 || mode == 1) {
        if (rnd.next(0, 1)) target = randomBits(n);
    } else if (mode == 2) {
        int operations = rnd.next(0, 5);
        for (int step = 0; step < operations; ++step) {
            applyOperation(target, 0, k, rnd.next(0, k - 1));
        }
    } else if (mode == 3) {
        int operations = rnd.next(1, 12);
        for (int step = 0; step < operations; ++step) {
            int left = rnd.next(0, n - k);
            int skipped = (step % 3 == 0) ? rnd.next(0, k - 1) : step % k;
            applyOperation(target, left, k, skipped);
        }
    } else if (mode == 4) {
        int changes = rnd.next(1, min(n, 4));
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < changes; ++i) target[positions[i]] ^= 1;
    } else if (mode == 5) {
        int operations = rnd.next(0, 20);
        for (int step = 0; step < operations; ++step) {
            int left;
            if (rnd.next(0, 2) == 0) {
                left = rnd.any(vector<int>{0, n - k});
            } else {
                left = rnd.next(0, n - k);
            }
            applyOperation(target, left, k, rnd.next(0, k - 1));
        }
    } else if (mode == 6) {
        target = randomBits(n);
    } else {
        int block = rnd.next(1, min(n, 8));
        int left = rnd.next(0, n - block);
        for (int i = left; i < left + block; ++i) target[i] ^= 1;
        if (rnd.next(0, 1)) {
            int operations = rnd.next(1, 6);
            for (int step = 0; step < operations; ++step) {
                applyOperation(target, rnd.next(0, n - k), k, rnd.next(0, k - 1));
            }
        }
    }

    println(n, k);
    println(current);
    println(target);

    return 0;
}
