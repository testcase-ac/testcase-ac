#include "testlib.h"
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of participants
    int N = rnd.next(1, 10);
    println(N);

    // Probability to duplicate an existing combination
    double dupProb = rnd.next() * 0.5;

    // Store generated combinations to allow duplicates
    vector<vector<int>> combos;
    combos.reserve(N);

    for (int i = 0; i < N; i++) {
        vector<int> cur;
        // Possibly duplicate a previous combination
        if (!combos.empty() && rnd.next() < dupProb) {
            cur = rnd.any(combos);
        } else {
            // Choose size c from 1..17, skewed by wnext
            int t = rnd.next(-2, 2);      // skew parameter
            int c = rnd.wnext(17, t) + 1; // gives [1..17]
            // Pick c distinct species from [1..17]
            vector<int> pool(17);
            for (int j = 0; j < 17; j++) pool[j] = j + 1;
            shuffle(pool.begin(), pool.end());
            pool.resize(c);
            sort(pool.begin(), pool.end());
            cur = pool;
        }
        combos.push_back(cur);
        // Output this participant
        printf("%d", (int)cur.size());
        for (int x : cur) printf(" %d", x);
        printf("\n");
    }

    return 0;
}
