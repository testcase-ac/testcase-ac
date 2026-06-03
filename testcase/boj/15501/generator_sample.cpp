#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> rotateBy(const vector<int>& values, int shift) {
    vector<int> result(values.size());
    int n = int(values.size());
    for (int i = 0; i < n; ++i) {
        result[i] = values[(i + shift) % n];
    }
    return result;
}

static bool sameOrder(const vector<int>& target, const vector<int>& candidate) {
    int n = int(target.size());
    for (int shift = 0; shift < n; ++shift) {
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (target[i] != candidate[(i + shift) % n]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return true;
        }
    }
    return false;
}

static bool reachable(const vector<int>& initial, vector<int> target) {
    if (sameOrder(target, initial)) {
        return true;
    }
    reverse(target.begin(), target.end());
    return sameOrder(target, initial);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 3);
    } else if (mode == 6) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(4, 18);
    }

    vector<int> initial(n);
    iota(initial.begin(), initial.end(), 1);
    if (mode >= 2) {
        shuffle(initial.begin(), initial.end());
    }

    vector<int> target = initial;
    if (mode == 0) {
        target = initial;
    } else if (mode == 1) {
        shuffle(target.begin(), target.end());
    } else if (mode == 2) {
        target = rotateBy(initial, rnd.next(0, n - 1));
    } else if (mode == 3) {
        reverse(target.begin(), target.end());
        target = rotateBy(target, rnd.next(0, n - 1));
    } else if (mode == 4) {
        do {
            target = initial;
            int left = rnd.next(0, n - 2);
            int right = rnd.next(left + 1, n - 1);
            swap(target[left], target[right]);
        } while (reachable(initial, target));
    } else {
        do {
            target = initial;
            shuffle(target.begin(), target.end());
        } while (reachable(initial, target));
    }

    println(n);
    println(initial);
    println(target);
    return 0;
}
