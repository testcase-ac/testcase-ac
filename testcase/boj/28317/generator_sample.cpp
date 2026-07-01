#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = n;
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        k = 1;
    } else if (mode == 3) {
        n = rnd.next(4, 24);
        k = rnd.next(2, min(n, 6));
    } else if (mode == 4) {
        n = rnd.next(10, 35);
        k = rnd.next(max(1, n / 2), n);
    } else if (mode == 5) {
        k = rnd.next(2, 8);
        n = rnd.next(k, min(40, 5 * k));
    } else {
        n = rnd.next(2, 30);
        k = rnd.next(1, n);
    }

    vector<int> bits(n);
    int pattern = rnd.next(0, 7);
    if (pattern == 0) {
        fill(bits.begin(), bits.end(), 0);
    } else if (pattern == 1) {
        fill(bits.begin(), bits.end(), 1);
    } else if (pattern == 2) {
        for (int i = 0; i < n; ++i) {
            bits[i] = i % 2;
        }
        if (rnd.next(0, 1)) {
            for (int& bit : bits) {
                bit ^= 1;
            }
        }
    } else if (pattern == 3) {
        int split = rnd.next(0, n);
        int left = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            bits[i] = (i < split ? left : 1 - left);
        }
    } else if (pattern == 4) {
        int block = rnd.next(1, max(1, min(k, 5)));
        int start = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            bits[i] = start ^ ((i / block) % 2);
        }
    } else if (pattern == 5) {
        int ones = rnd.next(0, min(n, 5));
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) {
            positions[i] = i;
        }
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < ones; ++i) {
            bits[positions[i]] = 1;
        }
    } else if (pattern == 6) {
        int zeros = rnd.next(0, min(n, 5));
        fill(bits.begin(), bits.end(), 1);
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) {
            positions[i] = i;
        }
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < zeros; ++i) {
            bits[positions[i]] = 0;
        }
    } else {
        double one_probability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            bits[i] = rnd.next() < one_probability;
        }
    }

    vector<int> sms;
    int window_sum = 0;
    for (int i = 0; i < k; ++i) {
        window_sum += bits[i];
    }
    sms.push_back(window_sum);
    for (int right = k; right < n; ++right) {
        window_sum += bits[right] - bits[right - k];
        sms.push_back(window_sum);
    }

    println(n, k);
    println(sms);
    return 0;
}
