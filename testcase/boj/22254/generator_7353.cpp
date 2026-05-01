#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small to medium N for hand verification
    int N = rnd.next(1, 20);
    vector<int> t(N);

    // Choose a pattern type for variability
    int type = rnd.next(0, 5);
    if (type == 0) {
        // Increasing sequence with small random steps
        int cur = rnd.next(1, 5);
        for (int i = 0; i < N; i++) {
            int step = rnd.next(1, 5);
            cur += step;
            t[i] = cur;
        }
    } else if (type == 1) {
        // Decreasing sequence: generate increasing then reverse
        int cur = rnd.next(1, 5);
        for (int i = 0; i < N; i++) {
            int step = rnd.next(1, 5);
            cur += step;
            t[i] = cur;
        }
        reverse(t.begin(), t.end());
    } else if (type == 2) {
        // Uniform random small tasks
        for (int i = 0; i < N; i++) {
            t[i] = rnd.next(1, 20);
        }
    } else if (type == 3) {
        // Many small, some heavy tasks
        for (int i = 0; i < N; i++) {
            if (rnd.next(0, 9) == 0) {
                t[i] = rnd.next(50, 100);
            } else {
                t[i] = rnd.next(1, 5);
            }
        }
    } else if (type == 4) {
        // All equal tasks
        int v = rnd.next(1, 20);
        for (int i = 0; i < N; i++) t[i] = v;
    } else {
        // Alternating small and medium tasks
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) t[i] = rnd.next(1, 5);
            else t[i] = rnd.next(10, 20);
        }
    }

    // Compute sum and max
    int sum = accumulate(t.begin(), t.end(), 0);
    int mx = *max_element(t.begin(), t.end());

    // Choose X relative to sum and max for edge cases
    int X;
    int xtype = rnd.next(0, 2);
    if (xtype == 0) {
        X = mx;              // tight bound
    } else if (xtype == 1) {
        X = sum;             // all on one line
    } else {
        if (sum > mx) X = rnd.next(mx, sum);
        else X = mx;
    }

    // Output
    println(N, X);
    println(t);

    return 0;
}
