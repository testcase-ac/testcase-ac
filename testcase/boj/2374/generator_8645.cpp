#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n with a bias towards small/medium sizes
    int n;
    int dice = rnd.next(0, 99);
    if (dice < 10) n = 1;
    else if (dice < 40) n = rnd.next(2, 5);
    else if (dice < 80) n = rnd.next(6, 10);
    else n = rnd.next(11, 15);

    vector<long long> a(n);

    // Choose pattern type
    int type = rnd.next(0, 9);

    switch (type) {
        case 0: { // all equal
            long long base;
            if (rnd.next(0, 99) < 70) base = rnd.next(1, 10);
            else base = rnd.next((int)1e8, (int)1e9);
            for (int i = 0; i < n; ++i) a[i] = base;
            break;
        }
        case 1: { // strictly increasing small steps
            long long base = rnd.next(1, 10);
            a[0] = base;
            for (int i = 1; i < n; ++i) {
                int inc = rnd.next(1, 5);
                a[i] = a[i - 1] + inc;
            }
            break;
        }
        case 2: { // strictly decreasing
            long long base = rnd.next(1, 10);
            a[0] = base;
            for (int i = 1; i < n; ++i) {
                int inc = rnd.next(1, 5);
                a[i] = a[i - 1] + inc;
            }
            // reverse to make it decreasing
            for (int i = 0; i < n / 2; ++i)
                swap(a[i], a[n - 1 - i]);
            break;
        }
        case 3: { // mountain (peak in the middle)
            if (n <= 2) {
                long long base = rnd.next(1, 10);
                for (int i = 0; i < n; ++i) a[i] = base + i;
                break;
            }
            int p = rnd.next(1, n - 2) + 0; // peak index in [1, n-2]
            long long peak = rnd.next(5, 20);
            a[p] = peak;
            for (int i = p - 1; i >= 0; --i) {
                long long dec = rnd.next(1, 3);
                a[i] = a[i + 1] - dec;
                if (a[i] < 1) a[i] = 1;
            }
            for (int i = p + 1; i < n; ++i) {
                long long dec = rnd.next(1, 3);
                a[i] = a[i - 1] - dec;
                if (a[i] < 1) a[i] = 1;
            }
            break;
        }
        case 4: { // valley (minimum in the middle)
            if (n <= 2) {
                long long base = rnd.next(1, 10);
                for (int i = 0; i < n; ++i) a[i] = base - i > 0 ? base - i : 1;
                break;
            }
            int p = rnd.next(1, n - 2) + 0; // valley index
            long long bottom = rnd.next(1, 5);
            a[p] = bottom;
            for (int i = p - 1; i >= 0; --i) {
                long long inc = rnd.next(1, 3);
                a[i] = a[i + 1] + inc;
            }
            for (int i = p + 1; i < n; ++i) {
                long long inc = rnd.next(1, 3);
                a[i] = a[i - 1] + inc;
            }
            break;
        }
        case 5: { // piecewise-constant segments
            int k = rnd.next(1, min(n, 7));
            vector<int> pos;
            for (int i = 1; i < n; ++i) pos.push_back(i);
            shuffle(pos.begin(), pos.end());
            pos.resize(max(0, k - 1));
            sort(pos.begin(), pos.end());

            vector<int> segStart;
            segStart.push_back(0);
            for (int x : pos) segStart.push_back(x);
            // segStart has k segment starts; last segment ends at n
            vector<long long> segVal;
            for (int s = 0; s < (int)segStart.size(); ++s) {
                long long val;
                if (s == 0 || rnd.next(0, 99) < 60) {
                    if (rnd.next(0, 1) == 0) val = rnd.next(1, 10);
                    else val = rnd.next(10, 50);
                } else if (rnd.next(0, 99) < 80) {
                    val = rnd.next((int)1e8, (int)1e9);
                } else {
                    val = segVal[rnd.next(0, s - 1)];
                }
                segVal.push_back(val);
            }
            for (int s = 0; s < (int)segStart.size(); ++s) {
                int L = segStart[s];
                int R = (s + 1 < (int)segStart.size() ? segStart[s + 1] : n);
                for (int i = L; i < R; ++i) a[i] = segVal[s];
            }
            break;
        }
        case 6: { // alternating two values
            long long v1 = rnd.next(1, 20);
            long long v2;
            do v2 = rnd.next(1, 20); while (v2 == v1);
            int startParity = rnd.next(0, 1);
            for (int i = 0; i < n; ++i) {
                if ((i + startParity) % 2 == 0) a[i] = v1;
                else a[i] = v2;
            }
            break;
        }
        case 7: { // random small values 1..5
            for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 5);
            break;
        }
        case 8: { // large values around a big base
            long long base = rnd.next((int)1e8, (int)1e9);
            long long hiOff = base < (long long)1e9 ? min(1000LL, 1000000000LL - base) : 0LL;
            long long loOff = -1000LL;
            for (int i = 0; i < n; ++i) {
                int off = rnd.next((int)loOff, (int)hiOff);
                long long v = base + off;
                if (v < 1) v = 1;
                if (v > (long long)1e9) v = (long long)1e9;
                a[i] = v;
            }
            break;
        }
        case 9: { // small random walk
            a[0] = rnd.next(1, 20);
            for (int i = 1; i < n; ++i) {
                int delta = rnd.next(-2, 2);
                long long v = a[i - 1] + delta;
                if (v < 1) v = 1;
                if (v > (long long)1e9) v = (long long)1e9;
                a[i] = v;
            }
            break;
        }
    }

    // Optional tweaks to create near-equal or slightly perturbed patterns
    bool allowTweak = true;
    if (type == 0 && rnd.next(0, 1) == 0) allowTweak = false; // keep some perfectly equal arrays
    if (allowTweak && rnd.next(0, 99) < 30 && n > 0) {
        int changes = rnd.next(1, min(3, n));
        for (int c = 0; c < changes; ++c) {
            int idx = rnd.next(0, n - 1);
            long long v = a[idx];
            if (v == 1) {
                v = v + rnd.next(1, 5);
            } else if (v >= (long long)1e9 - 5) {
                v = v - rnd.next(1, 5);
                if (v < 1) v = 1;
            } else {
                if (rnd.next(0, 1) == 0) v = v + rnd.next(1, 5);
                else v = max(1LL, v - rnd.next(1, 5));
            }
            if (v < 1) v = 1;
            if (v > (long long)1e9) v = (long long)1e9;
            if (v == a[idx]) v = a[idx] + 1 <= (long long)1e9 ? a[idx] + 1 : a[idx] - 1;
            a[idx] = v;
        }
    }

    // Output
    println(n);
    for (int i = 0; i < n; ++i) println(a[i]);

    return 0;
}
