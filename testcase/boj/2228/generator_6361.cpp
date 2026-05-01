#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N in small, medium, or larger hand-checkable ranges
    int N;
    int tN = rnd.next(2); // 0,1,2
    if (tN == 0) {
        N = rnd.next(1, 5);
    } else if (tN == 1) {
        N = rnd.next(6, 10);
    } else {
        N = rnd.next(11, 20);
    }
    // M between 1 and ceil(N/2)
    int M = rnd.next(1, (N + 1) / 2);

    // Prepare the array a of size N
    vector<int> a(N);
    // pattern to inject edge scenarios
    int pattern = rnd.next(9); // 0..9
    if (pattern == 0) {
        // all small positives
        for (int i = 0; i < N; ++i)
            a[i] = rnd.next(1, 10);
    } else if (pattern == 1) {
        // all small negatives
        for (int i = 0; i < N; ++i)
            a[i] = -rnd.next(1, 10);
    } else if (pattern == 2) {
        // larger magnitudes but mixed sign
        for (int i = 0; i < N; ++i)
            a[i] = (rnd.next(0, 1) ? 1 : -1) * rnd.next(1000, 5000);
    } else {
        // general random or clustered values
        bool bigVals = rnd.next(2) == 0;
        if (bigVals) {
            // fully random full-range
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(-32768, 32767);
        } else {
            // cluster flips: runs of same sign
            int curSign = rnd.next(0, 1) ? 1 : -1;
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 9) == 0) // 1/10 chance to flip sign
                    curSign = -curSign;
                int v = rnd.next(0, 10);
                a[i] = curSign * v;
            }
        }
    }

    // Output the generated test case
    println(N, M);
    for (int i = 0; i < N; ++i)
        println(a[i]);

    return 0;
}
