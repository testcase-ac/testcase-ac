#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        // Choose denominator small for hand-checkable cases
        int b = rnd.next(2, 20);
        int a;
        double p = rnd.next();
        // Hyper-parameter for special cases
        if (p < 0.1) {
            // trivial case a = 1
            a = 1;
        } else if (p < 0.2) {
            // near-whole fraction a = b-1
            a = b - 1;
        } else {
            // random coprime a
            do {
                a = rnd.next(1, b - 1);
            } while (std::gcd(a, b) != 1);
        }
        println(a, b);
    }
    return 0;
}
