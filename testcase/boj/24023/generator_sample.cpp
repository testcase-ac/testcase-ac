#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = (1 << 30) - 1;

int randomMask() {
    int bits = rnd.next(1, 30);
    int value = 0;
    for (int i = 0; i < bits; ++i) {
        value |= 1 << rnd.next(0, 29);
    }
    return value;
}

int randomSubmask(int mask) {
    int value = 0;
    for (int bit = 0; bit < 30; ++bit) {
        if ((mask & (1 << bit)) && rnd.next(0, 1)) {
            value |= 1 << bit;
        }
    }
    return value;
}

int positiveSubmask(int mask) {
    int value = randomSubmask(mask);
    if (value == 0) {
        vector<int> bits;
        for (int bit = 0; bit < 30; ++bit) {
            if (mask & (1 << bit)) {
                bits.push_back(bit);
            }
        }
        value = 1 << rnd.any(bits);
    }
    return value;
}

vector<int> buildSegmentWithOr(int k, int len) {
    vector<int> segment(len, 0);
    for (int bit = 0; bit < 30; ++bit) {
        if (k & (1 << bit)) {
            segment[rnd.next(0, len - 1)] |= 1 << bit;
        }
    }
    for (int& value : segment) {
        value |= randomSubmask(k);
        if (value == 0) {
            value = positiveSubmask(k);
        }
    }
    return segment;
}

int outsideBit(int k) {
    vector<int> bits;
    for (int bit = 0; bit < 30; ++bit) {
        if ((k & (1 << bit)) == 0) {
            bits.push_back(bit);
        }
    }
    if (bits.empty()) {
        return 0;
    }
    return 1 << rnd.any(bits);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k = randomMask();
    vector<int> a;

    if (mode == 0) {
        k = rnd.next(0, 1) ? 1 : MAX_VALUE;
        a.push_back(k);
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        int len = rnd.next(1, min(n, 8));
        int start = rnd.next(0, n - len);
        a.assign(n, 1);

        int blocker = outsideBit(k);
        for (int i = 0; i < n; ++i) {
            if (i < start || i >= start + len) {
                if (blocker != 0 && rnd.next(0, 2) == 0) {
                    a[i] = blocker | positiveSubmask(k);
                } else {
                    a[i] = positiveSubmask(k);
                }
            }
        }

        vector<int> segment = buildSegmentWithOr(k, len);
        for (int i = 0; i < len; ++i) {
            a[start + i] = segment[i];
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 30);
        int requiredBit = 1 << rnd.next(0, 29);
        k |= requiredBit;
        int allowed = k ^ requiredBit;
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            int value = allowed == 0 ? outsideBit(k) : positiveSubmask(allowed);
            if (value == 0) {
                value = MAX_VALUE ^ requiredBit;
            }
            a.push_back(value);
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 40);
        int blocker = outsideBit(k);
        if (blocker == 0) {
            k = randomMask() & ((1 << 29) - 1);
            if (k == 0) {
                k = 1;
            }
            blocker = 1 << 29;
        }
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(blocker | positiveSubmask(k));
            } else {
                a.push_back(positiveSubmask(k));
            }
        }
    } else {
        int n = rnd.next(20, 80);
        int len = rnd.next(4, 12);
        int start = rnd.next(0, n - len);
        a.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            a[i] = positiveSubmask(k);
        }
        vector<int> segment = buildSegmentWithOr(k, len);
        shuffle(segment.begin(), segment.end());
        for (int i = 0; i < len; ++i) {
            a[start + i] = segment[i];
        }
    }

    println((int)a.size(), k);
    println(a);
    return 0;
}
