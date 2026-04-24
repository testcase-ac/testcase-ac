#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable input
    int N = rnd.next(2, 10);
    int Q = rnd.next(1, 10);

    // Output N and Q
    println(N, Q);

    // Initial array with small values (including negatives)
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.next(-10, 10);
        printf("%lld%c", a[i], i+1==N?'\n':' ');
    }

    // Queries: each asks sum on [x,y] then updates position a_idx to b_val
    for (int i = 0; i < Q; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        if (x > y) swap(x, y);
        int a_idx = rnd.next(1, N);
        long long b_val = rnd.next(-10, 10);
        println(x, y, a_idx, b_val);
    }

    return 0;
}
