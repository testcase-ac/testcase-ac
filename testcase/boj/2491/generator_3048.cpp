#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length
    int N = rnd.next(1, 10);
    vector<int> a(N);

    // Choose a scenario for diversity
    int scen = rnd.next(0, 4);
    if (scen == 0) {
        // Completely random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(0, 9);
    } else if (scen == 1) {
        // One non-decreasing segment
        int L = rnd.next(1, N);
        int s = rnd.next(0, N - L);
        // fill prefix
        for (int i = 0; i < s; i++)
            a[i] = rnd.next(0, 9);
        // build non-decreasing
        int startVal = rnd.next(0, 9 - (L - 1));
        a[s] = startVal;
        for (int i = s + 1; i < s + L; i++)
            a[i] = a[i - 1] + rnd.next(0, 1);
        // fill suffix
        for (int i = s + L; i < N; i++)
            a[i] = rnd.next(0, 9);
    } else if (scen == 2) {
        // One non-increasing segment
        int L = rnd.next(1, N);
        int s = rnd.next(0, N - L);
        // fill prefix
        for (int i = 0; i < s; i++)
            a[i] = rnd.next(0, 9);
        // build non-increasing
        int startVal = rnd.next(L - 1, 9);
        a[s] = startVal;
        for (int i = s + 1; i < s + L; i++)
            a[i] = a[i - 1] - rnd.next(0, 1);
        // fill suffix
        for (int i = s + L; i < N; i++)
            a[i] = rnd.next(0, 9);
    } else if (scen == 3) {
        // Alternating high/low pattern
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0)
                a[i] = rnd.next(0, 4);
            else
                a[i] = rnd.next(5, 9);
        }
    } else {
        // All equal
        int x = rnd.next(0, 9);
        for (int i = 0; i < N; i++)
            a[i] = x;
    }

    // Output
    println(N);
    if (N > 0) println(a);
    return 0;
}
