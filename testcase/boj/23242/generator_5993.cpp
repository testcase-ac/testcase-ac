#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of data values and bucket limit
    int n = rnd.next(1, 30);
    int B = rnd.next(1, min(30, n));
    
    // Choose a generation mode for variability
    int mode = rnd.next(0, 2);
    vector<int> freq(n);
    
    if (mode == 0) {
        // Uniform random frequencies
        for (int i = 0; i < n; i++) {
            freq[i] = rnd.next(1, 100);
        }
    } else if (mode == 1) {
        // Monotonic trend (increasing or decreasing)
        bool inc = rnd.next(0, 1);
        if (inc) {
            freq[0] = rnd.next(1, 10);
            for (int i = 1; i < n; i++) {
                freq[i] = min(100, freq[i-1] + rnd.next(0, 10));
            }
        } else {
            freq[0] = rnd.next(50, 100);
            for (int i = 1; i < n; i++) {
                freq[i] = max(1, freq[i-1] - rnd.next(0, 10));
            }
        }
    } else {
        // Piecewise constant with noise
        int k = rnd.next(1, min(n, 5));
        vector<int> cuts;
        cuts.push_back(0);
        // pick k-1 cut points
        for (int i = 0; i < k-1; i++) {
            cuts.push_back(rnd.next(1, n-1));
        }
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        for (int seg = 0; seg < (int)cuts.size()-1; seg++) {
            int L = cuts[seg], R = cuts[seg+1];
            int base = rnd.next(1, 100);
            for (int i = L; i < R; i++) {
                int noise = rnd.next(0, 20) - 10; // -10 to +10
                int v = base + noise;
                if (v < 1) v = 1;
                if (v > 100) v = 100;
                freq[i] = v;
            }
        }
    }
    
    // Output the test case
    println(B);
    println(n);
    for (int x : freq) {
        println(x);
    }
    return 0;
}
