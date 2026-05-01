#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate small primes up to 1000
    const int MAXP = 1000;
    vector<bool> is_composite(MAXP+1, false);
    vector<ll> primes;
    for (int i = 2; i <= MAXP; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            if ((ll)i * i <= MAXP)
                for (int j = i * i; j <= MAXP; j += i)
                    is_composite[j] = true;
        }
    }
    // Choose n and number of distinct prime factors pcount
    int n = rnd.next(1, 600);
    int pcount = rnd.next(1, min(n, 6));
    // Pick pcount distinct primes
    shuffle(primes.begin(), primes.end());
    vector<ll> P(primes.begin(), primes.begin() + pcount);
    // Build a[] of size n, initially 1
    vector<ll> a(n, 1);
    vector<int> cnt(pcount, 0);
    // Ensure each prime appears at least once
    for (int i = 0; i < pcount; i++) {
        int j = rnd.next(0, n - 1);
        a[j] *= P[i];
        cnt[i]++;
    }
    // Fill remaining slots with random prime from P
    for (int j = 0; j < n; j++) {
        if (a[j] == 1) {
            int i = rnd.next(0, pcount - 1);
            a[j] *= P[i];
            cnt[i]++;
        }
    }
    // Shuffle the list for variability
    shuffle(a.begin(), a.end());
    // Output
    println(n);
    println(a);
    return 0;
}
