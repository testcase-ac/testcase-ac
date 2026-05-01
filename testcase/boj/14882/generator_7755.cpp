#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MOD = 786433;

    // Hyper-parameter for N: sometimes small, sometimes medium
    int N;
    if (rnd.next(2) == 0) N = rnd.next(0, 5);
    else N = rnd.next(6, 20);

    // Generate coefficients with special modes: all-zero, all-one, or random
    vector<int> a(N + 1);
    int mode = rnd.next(5); // 0..4
    if (mode == 0) {
        for (int i = 0; i <= N; i++) a[i] = 0;
    } else if (mode == 1) {
        for (int i = 0; i <= N; i++) a[i] = 1;
    } else {
        for (int i = 0; i <= N; i++) a[i] = rnd.next(0, MOD - 1);
    }

    // Hyper-parameter for K: sometimes small, sometimes medium
    int K;
    if (rnd.next(2) == 0) K = rnd.next(1, 5);
    else K = rnd.next(6, 20);

    // Generate query points with some guaranteed special values
    vector<int> xs(K);
    vector<int> specials = {0, 1, MOD - 1};
    int maxSpec = min((int)specials.size(), K);
    int cs = rnd.next(0, maxSpec);
    shuffle(specials.begin(), specials.end());
    for (int i = 0; i < cs; i++) xs[i] = specials[i];
    for (int i = cs; i < K; i++) xs[i] = rnd.next(0, MOD - 1);
    shuffle(xs.begin(), xs.end());

    // Output
    println(N);
    println(a);
    println(K);
    println(xs);

    return 0;
}
