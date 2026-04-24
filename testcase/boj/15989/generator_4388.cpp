#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for maximum n
    vector<int> maxn_opts = {5, 10, 20};
    int max_n = rnd.any(maxn_opts);
    // Hyper-parameter for number of test cases T
    int T = (rnd.next() < 0.7 ? rnd.next(1, 5) : rnd.next(6, 10));
    println(T);
    // Hyper-parameters for distribution of n
    vector<int> t_opts = {-2, 0, 2};
    for (int i = 0; i < T; i++) {
        int t = rnd.any(t_opts);
        int n;
        if (t == 0) {
            // uniform
            n = rnd.next(1, max_n);
        } else {
            // biased: t > 0 biases high, t < 0 biases low
            n = rnd.wnext(max_n, t) + 1;
        }
        println(n);
    }
    return 0;
}
