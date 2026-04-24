#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose small odd N
    vector<int> odds = {1, 3, 5, 7, 9, 11};
    int N = rnd.any(odds);

    // Mode: 0 = all zeros, 1 = all ones, 2 = random mix
    int mode = rnd.next(0, 2);
    vector<int> votes(N);

    if (mode == 0) {
        // all not cute
        for (int i = 0; i < N; i++) votes[i] = 0;
    } else if (mode == 1) {
        // all cute
        for (int i = 0; i < N; i++) votes[i] = 1;
    } else {
        // random mix with random probability
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++) {
            votes[i] = (rnd.next() < p ? 1 : 0);
        }
        // Guarantee majority for randomness if accidentally tie (shouldn't tie when N odd)
        int cnt1 = 0;
        for (int v : votes) if (v == 1) cnt1++;
        int cnt0 = N - cnt1;
        if (cnt1 <= cnt0) {
            // flip one to 1 to ensure majority of ones
            votes[rnd.next(0, N-1)] = 1;
        }
    }

    // Output
    println(N);
    for (int x : votes) {
        println(x);
    }
    return 0;
}
