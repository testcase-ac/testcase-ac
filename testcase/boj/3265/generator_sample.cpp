#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<int> buildPermutation(int n, int mode) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        return a;
    }
    if (mode == 1) {
        reverse(a.begin(), a.end());
        return a;
    }
    if (mode == 2) {
        int pos = 0;
        while (pos < n) {
            int len = min(n - pos, rnd.next(1, 5));
            shuffle(a.begin() + pos, a.begin() + pos + len);
            pos += len;
        }
        return a;
    }

    shuffle(a.begin(), a.end());
    return a;
}

vector<int> makeB(const vector<int>& a) {
    vector<int> b(a.size());
    int prefixMax = 0;
    for (int i = 0; i < int(a.size()); ++i) {
        prefixMax = max(prefixMax, a[i]);
        b[i] = (prefixMax == i + 1 ? 1 : 0);
    }
    return b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 8);
    } else if (sizeMode == 2) {
        n = rnd.next(9, 20);
    } else {
        n = rnd.next(21, 45);
    }

    vector<int> a = buildPermutation(n, rnd.next(0, 3));
    vector<int> b = makeB(a);

    int bMode = rnd.next(0, 4);
    if (bMode == 1) {
        b.assign(n, 0);
    } else if (bMode == 2) {
        b.assign(n, 0);
        b[n - 1] = 1;
    } else if (bMode == 3) {
        int flips = rnd.next(1, min(n, 3));
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(0, n - 1);
            b[pos] ^= 1;
        }
    }

    vector<int> positions(n);
    iota(positions.begin(), positions.end(), 1);
    shuffle(positions.begin(), positions.end());

    int mMode = rnd.next(0, 4);
    int m;
    if (mMode == 0) {
        m = 0;
    } else if (mMode == 1) {
        m = rnd.next(1, min(n, 3));
    } else if (mMode == 2) {
        m = rnd.next(1, min(n, 8));
    } else {
        m = n;
    }
    positions.resize(m);
    sort(positions.begin(), positions.end());

    vector<pair<int, int>> known;
    for (int pos : positions) {
        known.push_back({pos, a[pos - 1]});
    }

    println(n, m);
    println(b);
    for (auto [x, y] : known) {
        println(x, y);
    }

    return 0;
}
