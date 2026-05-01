#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of main string
    int N = rnd.next(1, 30);
    // Hyper-parameter: length of bomb string
    int L = rnd.next(1, 36);

    // Alphanumeric pool
    string alpha = "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "0123456789";

    // Build a bomb string with unique characters
    vector<char> pool(alpha.begin(), alpha.end());
    shuffle(pool.begin(), pool.end());
    string bomb;
    for (int i = 0; i < L; i++) bomb.push_back(pool[i]);

    string s;

    // With some probability generate a heavy-bomb case (repetitions)
    if (rnd.next(0, 9) == 0 && L <= N) {
        // Fill as many bombs as possible
        while ((int)s.size() + L <= N) {
            s += bomb;
        }
        // Fill remainder with random chars
        while ((int)s.size() < N) {
            s.push_back(rnd.any(alpha));
        }
    } else {
        // Normal case: randomly insert bombs and noise
        double bombProb = rnd.next(0.0, 1.0);
        while ((int)s.size() < N) {
            int remain = N - (int)s.size();
            if (remain >= L && rnd.next() < bombProb) {
                s += bomb;
            } else {
                s.push_back(rnd.any(alpha));
            }
        }
        if ((int)s.size() > N) s.resize(N);
    }

    // Output
    println(s);
    println(bomb);
    return 0;
}
