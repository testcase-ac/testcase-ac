#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_A = -1000000000;
const int MAX_A = 1000000000;

int randomValue() {
    return rnd.next(MIN_A, MAX_A);
}

int differentValue(int x) {
    if (x == MIN_A) {
        return rnd.next(MIN_A + 1, MAX_A);
    }
    if (x == MAX_A) {
        return rnd.next(MIN_A, MAX_A - 1);
    }
    return rnd.next(0, 1) == 0 ? rnd.next(MIN_A, x - 1) : rnd.next(x + 1, MAX_A);
}

vector<int> makeRunArray(int n, int maxRunLength) {
    vector<int> a;
    int previous = randomValue();
    while ((int)a.size() < n) {
        int value = differentValue(previous);
        int len = rnd.next(1, min(maxRunLength, n - (int)a.size()));
        for (int i = 0; i < len; ++i) {
            a.push_back(value);
        }
        previous = value;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        a.assign(n, randomValue());
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int first = randomValue();
        int second = differentValue(first);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? first : second);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        a = makeRunArray(n, rnd.next(2, 8));
    } else if (mode == 3) {
        n = rnd.next(4, 40);
        a = makeRunArray(n, rnd.next(1, 4));
        int tailLen = rnd.next(1, min(n, 12));
        int tailValue = differentValue(a[n - tailLen - (tailLen == n ? 0 : 1)]);
        for (int i = n - tailLen; i < n; ++i) {
            a[i] = tailValue;
        }
    } else if (mode == 4) {
        n = rnd.next(2, 24);
        vector<int> pool = {MIN_A, MAX_A, 0, -1, 1};
        int alphabetSize = rnd.next(2, (int)pool.size());
        for (int i = 0; i < n; ++i) {
            a.push_back(pool[rnd.next(0, alphabetSize - 1)]);
        }
    } else {
        n = rnd.next(30, 80);
        int center = rnd.next(-100, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back(center + rnd.next(-3, 3));
        }
    }

    println(n);
    println(a);
    return 0;
}
