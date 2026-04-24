#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand-checkable cases
    int N = rnd.next(1, 10);
    // True number of breakouts: at least 1 (day 1)
    int K = rnd.next(1, N);

    // Choose breakout days: day 1 is always a breakout
    vector<int> days;
    for (int i = 2; i <= N; i++) days.push_back(i);
    shuffle(days.begin(), days.end());
    vector<bool> is_break(N, false);
    is_break[0] = true;
    for (int i = 0; i < K-1; i++) {
        is_break[days[i]-1] = true;
    }

    // Build the true counter values
    vector<int> true_a(N);
    int last_break = 1;
    for (int i = 1; i <= N; i++) {
        if (is_break[i-1]) {
            true_a[i-1] = 0;
            last_break = i;
        } else {
            true_a[i-1] = i - last_break;
        }
    }

    // Decide how many entries to tamper
    int T = rnd.next(0, N);
    vector<int> idxs(N);
    for (int i = 0; i < N; i++) idxs[i] = i;
    shuffle(idxs.begin(), idxs.end());
    vector<bool> tampered(N, false);
    for (int i = 0; i < T; i++) {
        tampered[idxs[i]] = true;
    }

    // Generate final a_i with tampering
    const int MAX_VAL = 100;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        if (!tampered[i]) {
            a[i] = true_a[i];
        } else {
            // pick a wrong value in [0, MAX_VAL]
            int x;
            do {
                x = rnd.next(0, MAX_VAL);
            } while (x == true_a[i]);
            a[i] = x;
        }
    }

    // Output
    println(N);
    println(a);
    return 0;
}
