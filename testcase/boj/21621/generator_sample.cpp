#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxN = 100;
constexpr int kMaxSum = 1000000;

vector<int> splitPositive(int n, int total, int maxPart) {
    vector<int> parts(n, 1);
    int remaining = total - n;

    for (int i = 0; i < n && remaining > 0; ++i) {
        int add = rnd.next(0, min(remaining, maxPart - 1));
        parts[i] += add;
        remaining -= add;
    }

    int pos = 0;
    while (remaining > 0) {
        int add = min(remaining, maxPart - parts[pos]);
        parts[pos] += add;
        remaining -= add;
        pos = (pos + 1) % n;
    }

    shuffle(parts.begin(), parts.end());
    return parts;
}

vector<int> makeCase() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 6);
        vector<int> l(n);
        for (int& x : l) {
            x = rnd.next(1, 8);
        }
        return l;
    }

    if (mode == 1) {
        int n = rnd.next(2, 30);
        int value = rnd.next(1, 200);
        vector<int> l(n, value);
        if (rnd.next(0, 1)) {
            l[rnd.next(n)] = rnd.next(1, 200);
        }
        return l;
    }

    if (mode == 2) {
        int n = rnd.next(10, kMaxN);
        vector<int> l(n);
        for (int& x : l) {
            x = rnd.next(1, 50);
        }
        return l;
    }

    if (mode == 3) {
        int n = rnd.next(2, 25);
        vector<int> l(n);
        int smallSum = 0;
        for (int i = 1; i < n; ++i) {
            l[i] = rnd.next(1, 100);
            smallSum += l[i];
        }
        l[0] = rnd.next(max(1, smallSum), kMaxSum - smallSum);
        shuffle(l.begin(), l.end());
        return l;
    }

    if (mode == 4) {
        int n = rnd.next(2, kMaxN);
        int total = rnd.next(max(n, 900000), kMaxSum);
        return splitPositive(n, total, kMaxSum);
    }

    int n = rnd.next(1, kMaxN);
    int maxValue = rnd.next(1, 10000);
    vector<int> l;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int remainingSlots = n - i - 1;
        int hi = min(maxValue, kMaxSum - sum - remainingSlots);
        int x = rnd.next(1, hi);
        l.push_back(x);
        sum += x;
    }
    shuffle(l.begin(), l.end());
    return l;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> l = makeCase();
    println(static_cast<int>(l.size()));
    println(l);

    return 0;
}
