#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeChain(int n) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) p[i] = i - 1;
    return p;
}

vector<int> makeStar(int n) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) p[i] = 1;
    return p;
}

vector<int> makeKary(int n, int k) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) p[i] = max(1, (i - 2) / k + 1);
    return p;
}

vector<int> makeBroom(int n, int handle) {
    vector<int> p(n + 1);
    handle = min(handle, n);
    for (int i = 2; i <= handle; ++i) p[i] = i - 1;
    for (int i = handle + 1; i <= n; ++i) p[i] = handle;
    return p;
}

vector<int> makeRandomRecursive(int n) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) p[i] = rnd.next(1, i - 1);
    return p;
}

vector<int> makeMixed(int n) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (rnd.next(100) < 45) {
            p[i] = i - 1;
        } else if (rnd.next(100) < 70) {
            p[i] = 1;
        } else {
            p[i] = rnd.next(1, i - 1);
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int totalN = rnd.next(12, 80);
    int t = rnd.next(3, min(9, totalN / 2));
    vector<int> sizes;
    sizes.reserve(t);

    int remaining = totalN;
    for (int tc = 0; tc < t; ++tc) {
        int left = t - tc - 1;
        int n;
        if (tc == t - 1) {
            n = remaining;
        } else {
            int hi = min(18, remaining - 2 * left);
            n = rnd.next(2, hi);
        }
        sizes.push_back(n);
        remaining -= n;
    }
    shuffle(sizes.begin(), sizes.end());

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = sizes[tc];
        int mode = (tc + rnd.next(6)) % 6;
        vector<int> p;

        if (mode == 0) {
            p = makeChain(n);
        } else if (mode == 1) {
            p = makeStar(n);
        } else if (mode == 2) {
            p = makeKary(n, rnd.next(2, 4));
        } else if (mode == 3) {
            p = makeBroom(n, rnd.next(2, n));
        } else if (mode == 4) {
            p = makeRandomRecursive(n);
        } else {
            p = makeMixed(n);
        }

        p[1] = 0;
        println(n);
        vector<int> out;
        out.reserve(n);
        for (int i = 1; i <= n; ++i) out.push_back(p[i]);
        println(out);
    }

    return 0;
}
