#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: sometimes 1, otherwise 2..10
    int T;
    if (rnd.next() < 0.3) T = 1;
    else T = rnd.next(2, 10);
    println(T);
    // Generate diverse K values
    for (int i = 0; i < T; i++) {
        int K;
        double p = rnd.next(0.0, 1.0);
        if (p < 0.3) {
            // small K, edge cases including 1..10
            K = rnd.next(1, 10);
        } else if (p < 0.6) {
            // medium K
            K = rnd.next(11, 1000);
        } else {
            // large K up to 2^18-1
            K = rnd.next(1001, (1 << 18) - 1);
        }
        println(K);
    }
    return 0;
}
