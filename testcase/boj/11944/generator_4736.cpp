#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for biasing N towards small or large
    int bias = rnd.next(-3, 3);
    int N = rnd.wnext(20, bias) + 1;  // N in [1,20], biased by 'bias'
    // Compute total output length = digits(N) * N
    string s = to_string(N);
    int total_len = (int)s.size() * N;
    // Determine M with three cases: less, equal, greater than total_len
    int M_max = min(total_len * 2, 2016);
    double p = rnd.next();
    int M;
    if (p < 0.3 && total_len > 1) {
        M = rnd.next(1, total_len - 1);
    } else if (p < 0.6) {
        M = total_len;
    } else {
        M = rnd.next(total_len + 1, M_max);
    }
    // Output the test case
    println(N, M);
    return 0;
}
