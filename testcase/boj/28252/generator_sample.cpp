#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makePossibleSequence(int n) {
    vector<int> a(n);
    a[n - 1] = rnd.next(1, 2);

    if (n >= 2) {
        a[n - 2] = rnd.next(2, 8);
        for (int i = n - 3; i >= 0; --i) {
            a[i] = a[i + 1] + rnd.next(0, 4);
        }
    }

    return a;
}

static vector<int> makeLastTooLarge(int n) {
    vector<int> a = makePossibleSequence(n);
    a[n - 1] = rnd.next(3, 10);
    return a;
}

static vector<int> makePenultimateTooSmall(int n) {
    vector<int> a = makePossibleSequence(n);
    a[n - 2] = 1;
    if (n >= 3) {
        a[n - 3] = max(a[n - 3], a[n - 2]);
    }
    return a;
}

static vector<int> makeIncreasingBreak(int n) {
    vector<int> a(n);
    int value = rnd.next(1, 4);
    for (int i = 0; i < n; ++i) {
        value += rnd.next(0, 2);
        a[i] = value;
    }

    int pos = rnd.next(1, n - 1);
    a[pos] = a[pos - 1] + rnd.next(1, 5);
    return a;
}

static void shrinkToLimit(vector<int>& a) {
    while (true) {
        int sum = 0;
        for (int x : a) {
            sum += x;
        }
        if (sum <= 100000) {
            return;
        }

        int pos = max_element(a.begin(), a.end()) - a.begin();
        --a[pos];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a = {rnd.next(1, 6)};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        a = makePossibleSequence(n);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        a = makeLastTooLarge(n);
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        a = makePenultimateTooSmall(n);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        a = makeIncreasingBreak(n);
    } else {
        n = rnd.next(20, 60);
        a = makePossibleSequence(n);
        for (int& x : a) {
            x += rnd.next(0, 30);
        }
        sort(a.begin(), a.end(), greater<int>());
    }

    shrinkToLimit(a);

    println((int)a.size());
    println(a);

    return 0;
}
