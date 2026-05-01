#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of tasks: small enough for manual checking
    int N = rnd.next(1, 10);
    vector<int> T(N), S(N);

    // Random durations
    for (int i = 0; i < N; i++) {
        T[i] = rnd.next(1, 20);
    }

    // Choose a random execution order that will be feasible
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    // Build cumulative time and add variable slack to ensure feasibility
    int cum = 0, slack = 0;
    for (int j = 0; j < N; j++) {
        int i = order[j];
        cum += T[i];

        // Variable slack: mostly small, occasionally large
        int inc;
        int r = rnd.next(0, 9);
        if (r == 0) {
            // rare large slack
            inc = rnd.next(50, 100);
        } else if (r <= 3) {
            // small slack
            inc = rnd.next(0, 5);
        } else {
            // moderate slack
            inc = rnd.next(0, 20);
        }
        slack += inc;

        // Set deadline so that finishing tasks in 'order' up to j is feasible
        S[i] = cum + slack;
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(T[i], S[i]);
    }
    return 0;
}
