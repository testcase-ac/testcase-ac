#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(2, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int n = rnd.next(2, 10);
        println(n);

        // choose a mode for diversity
        int mode = rnd.next(0, 3);
        // minority case impossible if n == 2
        if (mode == 3 && n < 3) mode = rnd.next(0, 2);

        vector<int> votes(n, 1);
        if (mode == 0) {
            // uniform random small votes
            for (int i = 0; i < n; i++) {
                votes[i] = rnd.next(1, 50);
            }
        } else if (mode == 1) {
            // force clear majority
            int r = rnd.next(0, n - 1);
            int sum_other = 0;
            for (int i = 0; i < n; i++) {
                if (i == r) continue;
                votes[i] = rnd.next(1, 20);
                sum_other += votes[i];
            }
            int add = rnd.next(1, 20);
            votes[r] = sum_other + add;
        } else if (mode == 2) {
            // force tie for top (no winner)
            int k = rnd.next(2, n);
            vector<int> idx(n);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            int vhigh = rnd.next(1, 50);
            for (int i = 0; i < k; i++) {
                votes[idx[i]] = vhigh;
            }
            for (int i = k; i < n; i++) {
                votes[idx[i]] = rnd.next(1, vhigh);
            }
        } else {
            // mode == 3: minority winner (unique top but <= half)
            int r = rnd.next(0, n - 1);
            int sum_other = 0, max_other = 0;
            for (int i = 0; i < n; i++) {
                if (i == r) continue;
                votes[i] = rnd.next(1, 20);
                sum_other += votes[i];
                max_other = max(max_other, votes[i]);
            }
            // ensure unique top but votes[r] <= sum_other
            votes[r] = rnd.next(max_other + 1, sum_other);
        }

        // output votes
        for (int x : votes) {
            println(x);
        }
    }

    return 0;
}
