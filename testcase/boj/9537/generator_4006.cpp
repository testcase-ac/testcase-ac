#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Sequence length
        int n = rnd.next(1, 10);
        println(n);

        vector<ll> a;
        a.reserve(n);

        if (n == 1) {
            // Single element case
            a.push_back(rnd.next(1, 1000));
        } else {
            // Split into 1..4 segments to induce varying GCD blocks
            int maxSeg = min(n, 4);
            int s = rnd.next(1, maxSeg);
            vector<int> lengths(s);
            int rem = n;
            for (int i = 0; i < s; i++) {
                if (i == s - 1) {
                    lengths[i] = rem;
                } else {
                    // ensure at least 1 for each remaining segment
                    int minRemain = (s - i);
                    int maxLen = rem - (minRemain - 1);
                    lengths[i] = rnd.next(1, maxLen);
                    rem -= lengths[i];
                }
            }
            // Build each segment with a base GCD and occasional noise
            for (int i = 0; i < s; i++) {
                ll g = rnd.next(1, 20);
                for (int j = 0; j < lengths[i]; j++) {
                    if (rnd.next() < 0.2) {
                        // noise value
                        a.push_back(rnd.next(1, 1000));
                    } else {
                        // multiple of g
                        ll mul = rnd.next(1, 5);
                        a.push_back(g * mul);
                    }
                }
            }
            // Occasionally reverse the sequence to add diversity
            if (rnd.next() < 0.3) {
                reverse(a.begin(), a.end());
            }
        }

        // Output the sequence
        println(a);
    }

    return 0;
}
