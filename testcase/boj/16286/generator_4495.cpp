#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small size
    int n = rnd.next(1, 10);
    vector<int> w(n);
    long long W;
    int genCase = rnd.next(0, 2);
    if (genCase == 0) {
        // uniform weights and small W
        W = rnd.next(1, 20);
        for (int i = 0; i < n; i++) {
            w[i] = rnd.next(1, (int)W);
        }
    } else if (genCase == 1) {
        // random small weights, W between max and sum
        for (int i = 0; i < n; i++)
            w[i] = rnd.next(1, 10);
        int mx = *max_element(w.begin(), w.end());
        long long sum = accumulate(w.begin(), w.end(), 0LL);
        W = rnd.next(mx, (int)sum);
    } else {
        // one heavy weight plus small others, W somewhere between heavy and heavy+rest
        int heavyIdx = rnd.next(0, n - 1);
        for (int i = 0; i < n; i++) {
            if (i == heavyIdx) continue;
            w[i] = rnd.next(1, 10);
        }
        int bigVal = rnd.next(1, 100);
        w[heavyIdx] = bigVal;
        long long rest = accumulate(w.begin(), w.end(), 0LL) - bigVal;
        if (rest < 0) rest = 0;
        W = rnd.next(bigVal, (int)(bigVal + rest));
    }
    // maybe sort or reverse or leave as is
    int ord = rnd.next(0, 2);
    if (ord == 1) sort(w.begin(), w.end());
    else if (ord == 2) sort(w.begin(), w.end(), greater<int>());
    // output
    println(W, n);
    println(w);
    return 0;
}
