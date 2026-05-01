#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: grid size
    int n = rnd.next(1, 10);
    // Hyper-parameter: favorite number k
    int k;
    int kType = rnd.next(0, 4);
    if (kType == 0) {
        // trivial k = 1
        k = 1;
    } else if (kType == 1) {
        // small k
        k = rnd.next(1, 20);
    } else if (kType == 2) {
        // product of a few small primes
        vector<int> smallPrimes = {2,3,5,7,11,13,17,19,23,29,31};
        int cnt = rnd.next(1, 4);
        long long prod = 1;
        for (int i = 0; i < cnt; i++) {
            int p = rnd.any(smallPrimes);
            if (prod * p > 1000000) break;
            prod *= p;
        }
        if (prod == 1) prod = rnd.any(smallPrimes);
        k = int(prod);
    } else if (kType == 3) {
        // medium k
        k = rnd.next(50, 200);
    } else {
        // large k
        k = rnd.next(200000, 1000000);
    }

    // Factor k to get its prime divisors
    int temp = k;
    set<int> pfSet;
    for (int d = 2; (long long)d * d <= temp; d++) {
        if (temp % d == 0) {
            pfSet.insert(d);
            while (temp % d == 0) temp /= d;
        }
    }
    if (temp > 1) pfSet.insert(temp);
    vector<int> pf(pfSet.begin(), pfSet.end());

    // Hyper-parameter: obstacle probability
    double obsP;
    int oType = rnd.next(0, 3);
    if (oType == 0) {
        obsP = 0.0;
    } else if (oType == 1) {
        obsP = rnd.next(0.1, 0.2);
    } else if (oType == 2) {
        obsP = rnd.next(0.2, 0.5);
    } else {
        obsP = rnd.next(0.5, 0.9);
    }

    // Build grid
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool isStart = (i == 0 && j == 0);
            bool isEnd   = (i == n-1 && j == n-1);
            // place obstacle?
            if (!isStart && !isEnd && rnd.next() < obsP) {
                grid[i][j] = -1;
                continue;
            }
            // place candy number
            if (pf.empty() || rnd.next() < 0.3) {
                // random small candy
                grid[i][j] = rnd.next(1, 20);
            } else {
                // either a multiple of a prime factor or coprime
                if (rnd.next() < 0.5) {
                    int f = rnd.any(pf);
                    int maxMult = min(5, 1000000 / f);
                    if (maxMult < 1) maxMult = 1;
                    int m = rnd.next(1, maxMult);
                    grid[i][j] = f * m;
                } else {
                    int v;
                    do {
                        v = rnd.next(1, 20);
                        // ensure coprime with k
                    } while ([&]() {
                        for (int p : pf) if (v % p == 0) return true;
                        return false;
                    }());
                    grid[i][j] = v;
                }
            }
        }
    }

    // Output
    println(n, k);
    for (int i = 0; i < n; i++) {
        println(grid[i]);
    }
    return 0;
}
