#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long K_MAX = 1000000000000000000LL;

long long addCap(long long a, long long b) {
    if (a > K_MAX - b) {
        return K_MAX;
    }
    return a + b;
}

long long mul2Cap(long long x) {
    if (x > K_MAX / 2) {
        return K_MAX;
    }
    return 2 * x;
}

void attachChild(vector<int>& left, vector<int>& right, int parent, int child) {
    if (left[parent] == 0 && right[parent] == 0) {
        if (rnd.next(2) == 0) {
            left[parent] = child;
        } else {
            right[parent] = child;
        }
    } else if (left[parent] == 0) {
        left[parent] = child;
    } else {
        right[parent] = child;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 24);
    vector<int> left(n + 1, 0), right(n + 1, 0);

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            left[i] = i + 1;
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            right[i] = i + 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            int parent = i / 2;
            if (i % 2 == 0) {
                left[parent] = i;
            } else {
                right[parent] = i;
            }
        }
    } else {
        vector<int> open = {1};
        for (int child = 2; child <= n; ++child) {
            int idx = rnd.next((int)open.size());
            int parent = open[idx];
            attachChild(left, right, parent, child);
            if (left[parent] != 0 && right[parent] != 0) {
                open[idx] = open.back();
                open.pop_back();
            }
            open.push_back(child);
        }
    }

    if (mode == 4) {
        for (int i = 1; i <= n; ++i) {
            if ((left[i] == 0) != (right[i] == 0) && rnd.next(2) == 0) {
                swap(left[i], right[i]);
            }
        }
    }

    vector<long long> visits(n + 1, 0);
    for (int v = n; v >= 1; --v) {
        long long total = 1;
        if (left[v] != 0) {
            total = addCap(total, mul2Cap(visits[left[v]]));
        }
        if (right[v] != 0) {
            total = addCap(total, visits[right[v]]);
        }
        visits[v] = total;
    }

    vector<long long> candidates = {1, visits[1]};
    if (visits[1] >= 2) {
        candidates.push_back(2);
        candidates.push_back(rnd.next(1LL, visits[1]));
    }
    if (visits[1] >= 3) {
        candidates.push_back(visits[1] / 2);
        candidates.push_back(visits[1] - 1);
    }
    long long k = rnd.any(candidates);

    println(n, k);
    for (int i = 1; i <= n; ++i) {
        println(left[i], right[i]);
    }

    return 0;
}
