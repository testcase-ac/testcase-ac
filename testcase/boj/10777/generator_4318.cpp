#include "testlib.h"
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes for diversity
    int N = rnd.next(1, 10);
    int M = rnd.next(0, 5);

    // Hyper-parameter for A_i distribution
    int distA = rnd.next(0, 2);
    int loA, hiA;
    if (distA == 0)        { loA = 1;     hiA = 10; }
    else if (distA == 1)   { loA = 1;     hiA = 100; }
    else                   { loA = 50;    hiA = 100000; }

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(loA, hiA);
    }

    // Occasionally sort A ascending or descending
    if (N >= 2 && rnd.next() < 0.5) {
        if (rnd.next(0, 1) == 0) sort(A.begin(), A.end());
        else                  sort(A.begin(), A.end(), greater<int>());
    }

    // Occasionally introduce duplicates in A
    if (N >= 2 && rnd.next() < 0.3) {
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        if (i != j) A[j] = A[i];
    }

    // Hyper-parameter for B_i distribution
    int distB = rnd.next(0, 2);
    int loB, hiB;
    if (distB == 0)        { loB = 1;     hiB = 10; }
    else if (distB == 1)   { loB = 10;    hiB = 100; }
    else                   { loB = 100;   hiB = 100000; }

    vector<int> B(M);
    for (int i = 0; i < M; i++) {
        B[i] = rnd.next(loB, hiB);
    }

    // Occasionally sort B ascending or descending
    if (M >= 2 && rnd.next() < 0.5) {
        if (rnd.next(0, 1) == 0) sort(B.begin(), B.end());
        else                  sort(B.begin(), B.end(), greater<int>());
    }

    // Output the test case
    println(N);
    for (int x : A) println(x);
    println(M);
    for (int x : B) println(x);

    return 0;
}
