#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of test cases: small for hand-checking
    int T = rnd.next(1, 10);
    println(T);
    
    for (int i = 0; i < T; i++) {
        // Choose a category for N to ensure diversity
        int type = rnd.next(0, 4);
        long long N;
        const long long MAXN = 1000000000000000000LL;
        
        switch (type) {
            // Very small N
            case 0:
                N = rnd.next(1LL, 20LL);
                break;
            // Medium N
            case 1:
                N = rnd.next(21LL, 1000LL);
                break;
            // Fully random N in the entire range
            case 2:
                N = rnd.next(1LL, MAXN);
                break;
            // Near a power of two
            case 3: {
                int k = rnd.next(0, 60);
                long long base = (1LL << k);
                long long delta = rnd.next(-2LL, 2LL);
                N = base + delta;
                break;
            }
            // Near one less than a power of two
            case 4: {
                int k = rnd.next(1, 60);
                long long base = (1LL << k) - 1;
                long long delta = rnd.next(-2LL, 2LL);
                N = base + delta;
                break;
            }
        }
        // Clamp N to valid range
        if (N < 1) N = 1;
        if (N > MAXN) N = MAXN;
        
        // Output the test case
        println(N);
    }
    
    return 0;
}
