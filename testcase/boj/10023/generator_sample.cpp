#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int coinValue(const vector<int>& breeds, int target) {
    vector<int> dp(target + 1, 1000000);
    dp[0] = 0;
    for (int x = 1; x <= target; ++x) {
        for (int v : breeds) {
            if (x >= v) dp[x] = min(dp[x], dp[x - v] + 1);
        }
    }
    return dp[target];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, mode == 4 ? 100 : 14);
    int b = rnd.next(1, mode == 4 ? 20 : 8);

    vector<int> breeds;
    if (mode == 2) {
        b = rnd.next(1, 6);
        int base = 2 * rnd.next(1, 50);
        for (int i = 0; i < b; ++i) breeds.push_back(max(1, min(100, base + 2 * rnd.next(0, 6))));
    } else if (mode == 3) {
        b = rnd.next(2, 10);
        breeds.push_back(1);
        for (int i = 1; i < b; ++i) breeds.push_back(rnd.next(2, 100));
    } else {
        for (int i = 0; i < b; ++i) breeds.push_back(rnd.next(1, 100));
    }

    shuffle(breeds.begin(), breeds.end());

    vector<int> own(n, 0), heard(n, 0);
    if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int odd = 2 * rnd.next(0, 300) + 1;
            own[i] = min(99999, odd);
        }
    } else {
        int maxOwn = (mode == 4 ? 100000 : rnd.next(20, 350));
        for (int i = 0; i < n; ++i) {
            if (mode == 0) {
                own[i] = (rnd.next(100) < 35 ? 0 : rnd.next(0, maxOwn));
            } else if (mode == 1) {
                own[i] = rnd.next(0, 4) == 0 ? rnd.next(0, 3) : 0;
            } else if (mode == 3) {
                own[i] = rnd.next(0, maxOwn);
            } else {
                own[i] = rnd.next(0, maxOwn);
            }
            if (coinValue(breeds, min(own[i], 600)) > 10000 && mode != 4) own[i] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        int carried = (i == 0 ? 0 : max(0, heard[i - 1] - 1));
        heard[i] = min(100000, carried + own[i]);
    }

    if (mode == 2 && rnd.next(2) == 0) {
        int pos = rnd.next(n);
        heard[pos] = min(100000, heard[pos] + 1);
    }

    println(n, b);
    for (int v : breeds) println(v);
    for (int x : heard) println(x);
    return 0;
}
