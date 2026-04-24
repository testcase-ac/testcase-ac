#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of elements
    int n = rnd.next(2, 10);

    // Decide how many distinct values (to allow duplicates)
    int distinct_k = rnd.next(1, n);

    // Small prime list for generating numbers safely <=1e6
    vector<int> primes = {2, 3, 5, 7, 11};

    // Generate distinct numbers
    set<int> seen;
    vector<int> distinct_numbers;
    while ((int)distinct_numbers.size() < distinct_k) {
        int x;
        // With some probability include 1
        if (rnd.next() < 0.2) {
            x = 1;
        } else {
            // Choose 1 to 3 prime factors
            int kf = rnd.next(1, 3);
            // Shuffle primes and take first kf
            shuffle(primes.begin(), primes.end());
            x = 1;
            for (int i = 0; i < kf; i++) {
                int p = primes[i];
                int e = rnd.next(1, 2); // exponent 1 or 2
                while (e--) {
                    x *= p;
                }
            }
        }
        // Ensure uniqueness
        if (seen.insert(x).second) {
            distinct_numbers.push_back(x);
        }
    }

    // Build the array, allowing duplicates
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rnd.any(distinct_numbers);
    }
    // Shuffle positions for randomness
    shuffle(a.begin(), a.end());

    // Output
    println(n);
    for (int v : a) println(v);

    return 0;
}
