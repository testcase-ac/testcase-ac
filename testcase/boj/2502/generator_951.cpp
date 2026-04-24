#include "testlib.h"
using namespace std;

bool check_possible(int D, int K) {
    // Precompute Fibonacci numbers up to D
    int fib[31];
    fib[1] = 1;
    fib[2] = 1;
    for(int i = 3; i <= D; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    int coeff_a = fib[D-2];
    int coeff_b = fib[D-1];

    // Iterate over possible values of A
    for(int A = 1; A <= K / coeff_a; ++A) {
        int remaining = K - A * coeff_a;
        if(remaining < 0) continue;
        // Check if remaining is divisible by coeff_b
        if(remaining % coeff_b == 0) {
            int B = remaining / coeff_b;
            if(B >= A && B >= 1) {
                return true;
            }
        }
    }

    return false;
}

pair<int, int> gen_DK() {
    int D = rnd.next(3, 30);
    int K = rnd.next(10, 1000);
    if(rnd.next() < 0.2) {
        K = rnd.next(1000, 100000);
    }
    return make_pair(D, K);
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int D, K;
    tie(D, K) = gen_DK();
    while(!check_possible(D, K)) {
        tie(D, K) = gen_DK();
    }
    println(D, K);
}
