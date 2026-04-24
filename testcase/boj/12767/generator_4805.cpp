#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    int k = rnd.next(1, 8);
    println(n, k);

    // Hyper-parameters for diversity
    double sorted_prob = rnd.next(0.0, 1.0);   // probability to generate sorted-like sequences
    double large_prob  = rnd.next(0.0, 1.0);   // probability to generate large numbers
    int max_range_small = rnd.next(max(k, 5), 100);

    for (int i = 0; i < n; i++) {
        bool used_sorted = false;
        int max_range = (rnd.next() < large_prob ? 1000000 : max_range_small);
        vector<int> a;
        // Attempt to generate a sorted (or reverse-sorted) arithmetic sequence
        if (rnd.next() < sorted_prob) {
            int step = rnd.next(1, 10);
            int base_max = max_range - step * (k - 1);
            if (base_max >= 1) {
                int base = rnd.next(1, base_max);
                a.resize(k);
                for (int j = 0; j < k; j++) {
                    a[j] = base + step * j;
                }
                if (rnd.next() < 0.5) {
                    reverse(a.begin(), a.end());
                }
                used_sorted = true;
            }
        }
        // Otherwise, or if sorted attempt failed, generate random distinct values
        if (!used_sorted) {
            set<int> s;
            while ((int)s.size() < k) {
                s.insert(rnd.next(1, max_range));
            }
            a.assign(s.begin(), s.end());
            shuffle(a.begin(), a.end());
        }
        println(a);
    }

    return 0;
}
