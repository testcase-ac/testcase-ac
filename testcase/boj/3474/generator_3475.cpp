#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    // Special values at powers/multiples of 5 including the max boundary
    vector<int> specials = {5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, 9765625, 48828125, 244140625, 1000000000};
    for (int i = 0; i < T; i++) {
        double r = rnd.next();
        int N;
        if (r < 0.20) {
            // pick a special multiple-of-5 boundary
            N = rnd.any(specials);
        } else if (r < 0.35) {
            // very small N
            N = rnd.next(1, 4);
        } else if (r < 0.50) {
            // small N up to 10
            N = rnd.next(5, 10);
        } else if (r < 0.75) {
            // medium N up to 1000
            N = rnd.next(11, 1000);
        } else {
            // large N up to 1e9
            N = rnd.next(1001, 1000000000);
        }
        println(N);
    }
    return 0;
}
