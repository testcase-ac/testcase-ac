#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for easy hand-checking
    int N = rnd.next(2, 10);
    int M = rnd.next(1, 20);

    // Generate distinct stake positions in a small range
    int maxPos = rnd.next(5, 20);
    vector<int> posCand;
    for (int x = -maxPos; x <= maxPos; ++x)
        posCand.push_back(x);
    shuffle(posCand.begin(), posCand.end());
    vector<int> A(posCand.begin(), posCand.begin() + N);
    sort(A.begin(), A.end());

    // Compute maximum possible area for hyperparameterizing R
    int maxGap = 0;
    for (int i = 0; i + 1 < N; ++i)
        maxGap = max(maxGap, A[i+1] - A[i]);
    // Generate stick lengths
    int maxStick = rnd.next(M, 40);  // ensure at least M distinct sticks
    vector<int> stickCand;
    for (int b = 1; b <= maxStick; ++b)
        stickCand.push_back(b);
    shuffle(stickCand.begin(), stickCand.end());
    vector<int> B(stickCand.begin(), stickCand.begin() + M);

    int maxB = *max_element(B.begin(), B.end());
    double potentialMaxArea = (double)maxGap * maxB / 4.0;
    int hiR = max(1, (int)ceil(potentialMaxArea * 2));

    // Hyperparameter for R: sometimes tight, sometimes loose
    int R;
    if (rnd.next() < 0.5) {
        R = rnd.next(1, hiR);
    } else {
        R = rnd.next(1, hiR * 2);
    }

    // Shuffle input order for diversity
    shuffle(A.begin(), A.end());
    shuffle(B.begin(), B.end());

    // Output the generated test case
    println(N, M, R);
    println(A);
    println(B);

    return 0;
}
