#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

void appendBalancedOrder(vector<int>& out, int lo, int hi) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2;
    out.push_back(mid);
    if (rnd.next(2) == 0) {
        appendBalancedOrder(out, lo, mid - 1);
        appendBalancedOrder(out, mid + 1, hi);
    } else {
        appendBalancedOrder(out, mid + 1, hi);
        appendBalancedOrder(out, lo, mid - 1);
    }
}

vector<int> balancedPermutation(int n) {
    vector<int> p;
    appendBalancedOrder(p, 1, n);
    return p;
}

vector<int> nearSortedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int swaps = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, n - 1);
        int offset = rnd.next(-2, 2);
        int other = min(n - 1, max(0, pos + offset));
        swap(p[pos], p[other]);
    }
    return p;
}

vector<int> makePermutation(int n, int mode) {
    vector<int> p = identityPermutation(n);

    if (mode == 0) {
        return p;
    }
    if (mode == 1) {
        reverse(p.begin(), p.end());
        return p;
    }
    if (mode == 2) {
        return balancedPermutation(n);
    }
    if (mode == 3) {
        return nearSortedPermutation(n);
    }

    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 20;
        } else if (rnd.next(5) == 0) {
            n = rnd.next(16, 20);
        } else {
            n = rnd.next(2, 12);
        }

        vector<int> p = makePermutation(n, mode);
        println(n);
        println(p);
    }

    return 0;
}
