#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static void rotateRandomly(vector<int>& a) {
    int n = static_cast<int>(a.size());
    int shift = rnd.next(0, n - 1);
    rotate(a.begin(), a.begin() + shift, a.end());
}

static vector<int> randomComposition(int n) {
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i) {
        ++a[rnd.next(0, n - 1)];
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(3, 30);
    if (mode == 6) n = rnd.next(80, 180);

    vector<int> a(n, 1);

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        a.assign(n, 0);
        a[rnd.next(0, n - 1)] = n;
    } else if (mode == 2) {
        a.assign(n, 0);
        for (int i = 0; i < n / 2; ++i) a[i] = 2;
        if (n % 2 == 1) a[n / 2] = 1;
        rotateRandomly(a);
    } else if (mode == 3) {
        a.assign(n, 0);
        int surplusLen = rnd.next(1, max(1, n / 3));
        int remaining = n;
        for (int i = 0; i < surplusLen; ++i) {
            int value = (i == surplusLen - 1) ? remaining : rnd.next(1, remaining);
            a[i] = value;
            remaining -= value;
            if (remaining == 0) break;
        }
        rotateRandomly(a);
    } else if (mode == 4) {
        a.assign(n, 1);
        int moves = rnd.next(1, n);
        for (int i = 0; i < moves; ++i) {
            vector<int> donors;
            vector<int> receivers;
            for (int j = 0; j < n; ++j) {
                if (a[j] > 0) donors.push_back(j);
                receivers.push_back(j);
            }
            int from = rnd.any(donors);
            int to = rnd.any(receivers);
            if (from == to) continue;
            --a[from];
            ++a[to];
        }
    } else if (mode == 5) {
        a = randomComposition(n);
    } else {
        a = randomComposition(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) a[i] = 0;
        }
        int sum = accumulate(a.begin(), a.end(), 0);
        while (sum < n) {
            ++a[rnd.next(0, n - 1)];
            ++sum;
        }
        while (sum > n) {
            int pos = rnd.next(0, n - 1);
            if (a[pos] == 0) continue;
            --a[pos];
            --sum;
        }
    }

    println(n);
    println(a);
    return 0;
}
