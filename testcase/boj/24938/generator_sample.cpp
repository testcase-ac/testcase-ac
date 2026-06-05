#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 25);
    }

    int avg = rnd.next(1, 200);
    vector<int> a(n, avg);

    if (mode == 1) {
        int delta = rnd.next(0, min(avg - 1, 30));
        for (int& value : a) {
            value += rnd.next(-delta, delta);
        }
        long long sum = 0;
        for (int value : a) sum += value;
        int rem = int(sum % n);
        if (rem != 0) {
            a.back() += n - rem;
        }
    } else if (mode == 2) {
        int maxTransfer = min(200, (n - 1) * (avg - 1));
        int high = avg + rnd.next(0, maxTransfer);
        int pos = rnd.next(n);
        fill(a.begin(), a.end(), avg);
        a[pos] = high;
        int deficit = high - avg;
        while (deficit > 0) {
            int idx = rnd.next(n);
            if (idx == pos || a[idx] == 1) continue;
            --a[idx];
            --deficit;
        }
    } else if (mode == 3) {
        int step = rnd.next(1, min(avg, 20));
        for (int i = 0; i < n; ++i) {
            a[i] = avg + (i - n / 2) * step;
        }
        int minValue = *min_element(a.begin(), a.end());
        if (minValue < 1) {
            for (int& value : a) value += 1 - minValue;
        }
        long long sum = 0;
        for (int value : a) sum += value;
        int rem = int(sum % n);
        if (rem != 0) {
            a.back() += n - rem;
        }
    } else if (mode == 4) {
        int delta = rnd.next(1, min(avg, 80));
        for (int i = 0; i + 1 < n; i += 2) {
            a[i] += delta;
            a[i + 1] -= delta;
        }
    } else if (mode == 5) {
        int delta = rnd.next(1, min(avg, 60));
        int l = rnd.next(0, n - 2);
        int r = rnd.next(l + 1, n - 1);
        a[l] += delta;
        a[r] -= delta;
    } else if (mode == 6) {
        int changes = rnd.next(1, 4 * n);
        for (int iter = 0; iter < changes; ++iter) {
            int from = rnd.next(n);
            int to = rnd.next(n);
            if (from == to || a[from] == 1) continue;
            int delta = rnd.next(1, min(a[from] - 1, 50));
            a[from] -= delta;
            a[to] += delta;
        }
    }

    for (int& value : a) {
        value = max(1, min(value, 1000000));
    }

    println(n);
    println(a);

    return 0;
}
