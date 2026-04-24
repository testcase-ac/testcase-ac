#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of gifts
    int n = rnd.next(1, 10);
    // maximum number of half-price discounts
    int a = rnd.next(0, n);
    // choose max price cap
    vector<long long> caps = {10, 100, 1000, 1000000000LL};
    long long pxMax = rnd.any(caps);
    long long xMax = pxMax / 2;
    if (xMax < 1) xMax = 1;
    // choose price distribution: 0=uniform,1=small bias,2=large bias
    int dist = rnd.next(0, 2);
    vector<long long> prices;
    for (int i = 0; i < n; i++) {
        long long x;
        if (dist == 0) {
            x = rnd.next(1LL, xMax);
        } else if (dist == 1) {
            x = rnd.wnext(xMax, 1) + 1;
        } else {
            x = rnd.wnext(xMax, -1) + 1;
        }
        prices.push_back(x * 2);
    }
    shuffle(prices.begin(), prices.end());
    long long total = accumulate(prices.begin(), prices.end(), 0LL);
    long long bUpper = min(total, 1000000000LL);
    if (bUpper < 1) bUpper = 1;
    long long b = rnd.next(1LL, bUpper);
    // output
    println(n, b, a);
    println(prices);
    return 0;
}
