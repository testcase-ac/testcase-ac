#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of sequence
    int N = rnd.next(1, 10);

    // Hyper-parameters for value range
    int lowVal = rnd.next(0, 5);
    int rangeSize = rnd.next(0, 20);
    int highVal = lowVal + rangeSize;

    // Hyper-parameter: mode of sequence shape
    // 0 = random, 1 = non-decreasing, 2 = non-increasing, 3 = constant
    int mode = rnd.next(0, 3);

    vector<long long> a(N);
    if (mode == 3) {
        // constant sequence
        long long v = rnd.next(lowVal, highVal);
        for (int i = 0; i < N; i++)
            a[i] = v;
    } else {
        // random sequence then maybe sorted
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(lowVal, highVal);
        if (mode == 1) {
            sort(a.begin(), a.end());
        } else if (mode == 2) {
            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
        }
    }

    // Hyper-parameter: choose P relative to [lowVal, highVal]
    int pMode = rnd.next(0, 2);
    long long P;
    if (pMode == 0) {
        // P at or below the minimum
        P = rnd.next(0, lowVal);
    } else if (pMode == 1) {
        // P inside the value range
        P = rnd.next(lowVal, highVal);
    } else {
        // P above the maximum
        P = rnd.next(highVal, highVal + 10);
    }

    // Output in problem format
    println(N);
    println(a);
    println(P);

    return 0;
}
