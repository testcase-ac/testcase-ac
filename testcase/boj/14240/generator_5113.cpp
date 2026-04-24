#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of sequence
    int n = rnd.next(1, 10);

    // Hyper-parameter: absolute bound for values
    vector<int> bounds = {3, 10, 100, 1000};
    int B = rnd.any(bounds);

    // Hyper-parameter: pattern type
    // 0 = uniform random
    // 1 = mostly positive
    // 2 = mostly negative
    // 3 = monotonic increasing
    // 4 = monotonic decreasing
    int pat = rnd.next(0, 4);

    vector<int> s(n);
    if (pat == 0) {
        // Uniform random in [-B, B]
        for (int i = 0; i < n; i++) {
            s[i] = rnd.next(-B, B);
        }
    } else if (pat == 1) {
        // Mostly positive
        for (int i = 0; i < n; i++) {
            if (rnd.next() < 0.8)
                s[i] = rnd.next(0, B);
            else
                s[i] = rnd.next(-B, 0);
        }
    } else if (pat == 2) {
        // Mostly negative
        for (int i = 0; i < n; i++) {
            if (rnd.next() < 0.8)
                s[i] = rnd.next(-B, 0);
            else
                s[i] = rnd.next(0, B);
        }
    } else if (pat == 3) {
        // Monotonic non-decreasing
        int halfB = B / 2;
        s[0] = rnd.next(-halfB, halfB);
        int incMax = max(1, B / 4);
        for (int i = 1; i < n; i++) {
            s[i] = s[i-1] + rnd.next(0, incMax);
            if (s[i] > B) s[i] = B;
        }
    } else {
        // Monotonic non-increasing
        int halfB = B / 2;
        s[0] = rnd.next(-halfB, halfB);
        int decMax = max(1, B / 4);
        for (int i = 1; i < n; i++) {
            s[i] = s[i-1] - rnd.next(0, decMax);
            if (s[i] < -B) s[i] = -B;
        }
    }

    // Output
    println(n);
    println(s);

    return 0;
}
