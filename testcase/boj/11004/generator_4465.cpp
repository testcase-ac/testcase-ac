#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small array size
    int N = rnd.next(1, 10);
    int K = rnd.next(1, N);

    // Hyper-parameter: control the range width to influence duplicates
    int maxWidth = 20;
    int width = rnd.next(0, maxWidth);
    // Ensure lowBound <= highBound and keep numbers small for hand-check
    int lowBound = rnd.next(-10, 10 - width);
    int highBound = lowBound + width;

    // Hyper-parameter: control the order of the array
    double orderPick = rnd.next();
    bool doSort = orderPick < 0.2;
    bool doReverse = orderPick >= 0.2 && orderPick < 0.4;

    // Generate the array
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(lowBound, highBound);
    }
    if (doSort) {
        sort(A.begin(), A.end());
    } else if (doReverse) {
        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());
    }
    
    // Output
    println(N, K);
    println(A);

    return 0;
}
