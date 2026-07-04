#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n;
    int k;
    int targetM;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 30);
        targetM = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        k = rnd.next(20, 200);
        targetM = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(19LL, 1000000000LL);
        k = rnd.next(2, 80);
        targetM = rnd.next(1, 10);
    } else if (mode == 3) {
        n = rnd.next(1LL, 1000000000LL);
        k = rnd.next(50000, 200000);
        targetM = rnd.next(3, 16);
    } else if (mode == 4) {
        n = rnd.any(vector<long long>{1LL, 2LL, 18LL, 19LL, 1000000000LL});
        k = rnd.any(vector<int>{1, 2, 6, 30, 199999, 200000});
        targetM = rnd.next(1, 10);
    } else {
        n = rnd.next(1LL, 1000000000LL);
        k = rnd.next(1, 200000);
        targetM = rnd.next(1, 20);
    }

    set<long long> values;
    if (rnd.next(0, 1) == 1 || mode == 2) {
        values.insert(1);
    }

    vector<long long> candidates;
    for (int v = 2; v <= min(k, 40); ++v) {
        candidates.push_back(v);
    }
    for (int d = 1; d * d <= k; ++d) {
        if (k % d == 0) {
            candidates.push_back(d);
            candidates.push_back(k / d);
        }
    }
    candidates.push_back(k);
    if (k > 1) {
        candidates.push_back(k - 1);
    }
    candidates.push_back(1000000000LL);
    candidates.push_back(999999999LL);
    candidates.push_back(1LL * k + rnd.next(1, 1000));

    shuffle(candidates.begin(), candidates.end());
    for (long long value : candidates) {
        if ((int)values.size() >= targetM) {
            break;
        }
        if (1 <= value && value <= 1000000000LL) {
            values.insert(value);
        }
    }

    while ((int)values.size() < targetM) {
        long long value;
        if (rnd.next(0, 99) < 75) {
            value = rnd.next(1, max(1, k));
        } else {
            value = rnd.next(1LL, 1000000000LL);
        }
        values.insert(value);
    }

    vector<long long> x(values.begin(), values.end());
    println(n, (int)x.size(), k);
    println(x);

    return 0;
}
