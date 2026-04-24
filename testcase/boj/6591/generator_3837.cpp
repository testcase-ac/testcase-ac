#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases (excluding the terminating "0 0")
    int T = rnd.next(1, 10);
    // weight choices for wnext
    vector<int> weights = { -2, -1, 0, 1, 2 };
    for (int i = 0; i < T; i++) {
        // Hyper-parameter to bias n toward small or large end of [1,20]
        int t_n = rnd.any(weights);
        int raw_n = rnd.wnext(20, t_n);
        int n = max(1, raw_n);
        // Hyper-parameter to bias k in [0,n]
        int t_k = rnd.any(weights);
        int raw_k = rnd.wnext(n + 1, t_k); // gives 0..n
        int k = min(max(0, raw_k), n);
        println(n, k);
    }
    // Terminator
    println(0, 0);
    return 0;
}
