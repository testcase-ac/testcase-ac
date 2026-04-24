#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int L = rnd.next(0, 10);
    int R = rnd.next(L, L + 10);
    int type = rnd.next(0, 3); // 0: random, 1: sorted asc, 2: sorted desc, 3: all equal

    vector<int> A(N);
    if (type == 3) {
        // all equal
        int v = rnd.next(L, R);
        for (int i = 0; i < N; i++) A[i] = v;
    } else {
        // fill with random values in [L, R]
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(L, R);
        }
        if (type == 1) {
            sort(A.begin(), A.end());
        } else if (type == 2) {
            sort(A.begin(), A.end(), greater<int>());
        }
    }

    // Output
    println(N);
    println(A);

    return 0;
}
