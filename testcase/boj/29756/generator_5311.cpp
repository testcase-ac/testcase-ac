#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N bias: negative -> small N, positive -> large N
    int t_n = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int N = rnd.wnext(10, t_n) + 1;    // N in [1,10]

    // Recovery per section
    int K = rnd.next(1, 10);

    // Hyper-parameters for score and health biases
    int t_s = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int t_h = rnd.any(vector<int>{-2, -1, 0, 1, 2});

    vector<int> s(N), h(N);
    // Generate scores s_i in [1,20], with bias t_s
    for (int i = 0; i < N; ++i)
        s[i] = rnd.wnext(20, t_s) + 1;
    // Generate health costs h_i in [1,20], with bias t_h
    for (int i = 0; i < N; ++i)
        h[i] = rnd.wnext(20, t_h) + 1;

    // Ensure at least one segment is impossible (h_i > K) if possible
    if (K < 20 && N > 0) {
        int pos = rnd.next(0, N - 1);
        h[pos] = rnd.next(K + 1, 20);
    }
    // Ensure at least one segment is always playable (h_i <= K)
    if (K > 1 && N > 1) {
        int pos = rnd.next(0, N - 1);
        h[pos] = rnd.next(1, min(K, 20));
    }

    // Output
    println(N, K);
    println(s);
    println(h);

    return 0;
}
