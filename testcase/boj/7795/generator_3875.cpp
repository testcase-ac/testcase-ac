#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Sizes of A and B
        int N = rnd.next(1, 10);
        int M = rnd.next(1, 10);
        println(N, M);

        // Maximum value for this test
        // half the time small range [5,20], half the time larger [21,1000]
        int maxVal = (rnd.next() < 0.5 ? rnd.next(5, 20) : rnd.next(21, 1000));

        // Prepare low and high sub-ranges for biasing
        int lowHi = max(1, maxVal / 3);
        int highLo = min(maxVal, lowHi + 1);

        // Bias type: 0 = no bias, 1 = A small, B large, 2 = A large, B small
        int bias = rnd.next(0, 2);
        pair<int,int> rangeA, rangeB;
        if (bias == 1) {
            rangeA = {1, lowHi};
            rangeB = {highLo, maxVal};
        } else if (bias == 2) {
            rangeA = {highLo, maxVal};
            rangeB = {1, lowHi};
        } else {
            rangeA = {1, maxVal};
            rangeB = {1, maxVal};
        }

        // Generate A with possible duplicates
        int uniqA = rnd.next(1, N);
        vector<int> poolA;
        for (int i = 0; i < uniqA; i++)
            poolA.push_back(rnd.next(rangeA.first, rangeA.second));
        vector<int> A(N);
        for (int i = 0; i < N; i++)
            A[i] = rnd.any(poolA);
        if (rnd.next() < 0.5)
            shuffle(A.begin(), A.end());
        else
            sort(A.begin(), A.end());
        println(A);

        // Generate B with possible duplicates
        int uniqB = rnd.next(1, M);
        vector<int> poolB;
        for (int i = 0; i < uniqB; i++)
            poolB.push_back(rnd.next(rangeB.first, rangeB.second));
        vector<int> B(M);
        for (int i = 0; i < M; i++)
            B[i] = rnd.any(poolB);
        if (rnd.next() < 0.5)
            shuffle(B.begin(), B.end());
        else
            sort(B.begin(), B.end());
        println(B);
    }

    return 0;
}
