#include "testlib.h"
#include <vector>
using namespace std;

int otherCandidate(int n) {
    if (n == 1) return 1;
    return rnd.next(2, n);
}

void fillOthers(vector<int>& a, int n) {
    for (int& x : a) {
        if (x != 1) x = otherCandidate(n);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int mode = n < 3 ? rnd.next(0, 2) : rnd.next(0, 5);
    vector<int> a(n, 0);

    if (n == 1) {
        a[0] = 1;
    } else if (mode == 0) {
        int ones = rnd.next((n + 1) / 2, n);
        for (int i = 0; i < ones; ++i) a[i] = 1;
        fillOthers(a, n);
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        int len = rnd.next(1, n);
        int ones = rnd.next((len + 1) / 2, len);
        for (int i = 0; i < ones; ++i) a[i] = 1;
        fillOthers(a, n);
    } else if (mode == 2) {
        int len = rnd.next(1, n);
        int ones = rnd.next((len + 1) / 2, len);
        for (int i = 0; i < ones; ++i) a[n - 1 - i] = 1;
        fillOthers(a, n);
    } else if (mode == 3) {
        fillOthers(a, n);
        int l = rnd.next(1, n - 2);
        int r = rnd.next(l, n - 2);
        int count = rnd.next(1, r - l + 1);
        vector<int> pos;
        for (int i = l; i <= r; ++i) pos.push_back(i);
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < count; ++i) a[pos[i]] = 1;
    } else {
        int blockLen = rnd.next(1, n);
        int start = rnd.next(0, n - blockLen);
        int ones = rnd.next(1, blockLen);
        fillOthers(a, n);
        vector<int> pos;
        for (int i = start; i < start + blockLen; ++i) pos.push_back(i);
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < ones; ++i) a[pos[i]] = 1;
    }

    println(n);
    println(a);
    return 0;
}
