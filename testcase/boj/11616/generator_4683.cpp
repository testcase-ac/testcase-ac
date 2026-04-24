#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small n
    int n = rnd.next(1, 10);

    // Choose m in [1,20], skewed for diversity
    int skew = rnd.next(-1, 1);         // -1: small, 0: uniform, 1: large
    int m0 = rnd.wnext(20, skew);       // produces in [0,19]
    int m = m0 + 1;                     // shift to [1,20]

    // Zero probability skewed for diversity
    int zp = rnd.wnext(101, rnd.next(-1, 1)); // [0,100]
    double zeroProb = zp / 100.0;

    // Build digit string
    string s;
    s.reserve(n);
    for (int i = 0; i < n; i++) {
        if (rnd.next() < zeroProb) {
            s.push_back('0');
        } else {
            // random digit from '1'..'9'
            char d = char('1' + rnd.next(0, 8));
            s.push_back(d);
        }
    }

    // Output
    println(n, m);
    printf("%s\n", s.c_str());

    return 0;
}
