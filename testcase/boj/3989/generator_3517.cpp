#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter: choose M small, prime vs composite
    vector<int> primes = {3,5,7,11,13,17,19};
    vector<int> comps = {4,6,8,9,10,12,14,15,16,18,20};
    int M = (rnd.next(0,1) == 0 ? rnd.any(primes) : rnd.any(comps));
    // Hyperparameter: choose N either small or large relative to M
    int N;
    if (rnd.next(0,1) == 0) {
        N = rnd.next(1, min(3, M-1));
    } else {
        N = rnd.next(max(1, (M-1)/2), M-1);
    }
    // Generate distinct initial infected people
    vector<int> init(M);
    for (int i = 0; i < M; i++) init[i] = i;
    shuffle(init.begin(), init.end());
    init.resize(N);
    sort(init.begin(), init.end());
    // Hyperparameter: choose K small or very large
    long long K;
    if (rnd.next(0,1) == 0) {
        K = rnd.next(1LL, 10LL);
    } else {
        K = rnd.next(1000000000000LL, 1000000000000000000LL);
    }
    // Output the test case
    println(K, M, N);
    println(init);
    return 0;
}
