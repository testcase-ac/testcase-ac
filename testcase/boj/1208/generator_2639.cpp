/* generator code */
#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a small N to keep the test hand-checkable
    int N = rnd.next(1, 8);
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.next(-100000, 100000);
    }

    // Ensure at least one valid subset by picking a random non-empty subset
    int maskMax = 1 << N;
    int mask = rnd.next(1, maskMax - 1);
    long long S = 0;
    for (int i = 0; i < N; i++) {
        if (mask & (1 << i)) S += a[i];
    }

    // Output
    println(N, S);
    for (int i = 0; i < N; i++) {
        printf("%d%c", a[i], i + 1 == N ? '\n' : ' ');
    }
    return 0;
}
