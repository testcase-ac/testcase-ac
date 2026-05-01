#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a small N for hand checking
    int N = rnd.next(2, 10);
    vector<int> A(N), B(N);
    // Random distributions for A and B
    bool skewA = rnd.next() < 0.5;
    int tA = rnd.next(1, 3);
    bool skewB = rnd.next() < 0.5;
    int tB = rnd.next(-3, -1);
    // Generate values
    for (int i = 0; i < N; i++) {
        if (skewA) A[i] = rnd.wnext(101, tA);
        else       A[i] = rnd.next(0, 100);
        if (skewB) B[i] = rnd.wnext(101, tB);
        else       B[i] = rnd.next(0, 100);
    }
    // Shuffle A to create permutation; B stays in original sequence
    shuffle(A.begin(), A.end());
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%d", A[i]);
        if (i + 1 < N) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d", B[i]);
        if (i + 1 < N) printf(" ");
    }
    printf("\n");
    return 0;
}
