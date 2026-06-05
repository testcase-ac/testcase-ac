#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> positiveParts(int count, int sum) {
    vector<int> parts(count, 1);
    sum -= count;
    for (int i = 0; i < count && sum > 0; ++i) {
        int add = rnd.next(0, min(20, sum));
        parts[i] += add;
        sum -= add;
    }
    while (sum > 0) {
        int i = rnd.next(count);
        int add = min(sum, rnd.next(1, 50));
        parts[i] += add;
        sum -= add;
    }
    shuffle(parts.begin(), parts.end());
    return parts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> d;

    if (mode == 0) {
        d = {rnd.next(0, 3) == 0 ? 1 : rnd.next(2, 100000)};
    } else if (mode == 1) {
        int n = rnd.next(2, 15);
        int value = rnd.next(1, 30);
        d.assign(n, value);
    } else if (mode == 2) {
        int n = rnd.next(2, 15);
        int restSum = rnd.next(n - 1, min(100000, 12 * (n - 1)));
        d = positiveParts(n - 1, restSum);
        d.push_back(restSum);
    } else if (mode == 3) {
        int n = rnd.next(2, 15);
        int restSum = rnd.next(n - 1, min(99980, 10 * (n - 1)));
        d = positiveParts(n - 1, restSum);
        d.push_back(restSum + rnd.next(1, min(100000 - restSum, 25)));
    } else if (mode == 4) {
        int n = rnd.next(2, 25);
        int lo = rnd.next(1, 10);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(lo, hi));
    } else {
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            d.push_back(rnd.next(1, 100000));
        }
    }

    shuffle(d.begin(), d.end());
    println((int)d.size());
    println(d);

    return 0;
}
