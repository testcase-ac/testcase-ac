/* generator code */
#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose length N between 1 and 10 (so it's hand-checkable)
    int N = rnd.next(1, 10);
    // Decide on a bias strategy for digits: uniform, max‐biased, or min‐biased
    int bias = rnd.next(0, 2);

    // Build the N-digit string (leading zeros allowed)
    string s(N, '0');
    for (int i = 0; i < N; ++i) {
        int d;
        if (bias == 0) {
            // Uniform digit
            d = rnd.next(0, 9);
        } else if (bias == 1) {
            // Take max of t samples to bias toward larger digits
            int t = rnd.next(1, 5);
            d = rnd.wnext(10, t);
        } else {
            // Take min of t samples to bias toward smaller digits
            int t = rnd.next(1, 5);
            d = rnd.wnext(10, -t);
        }
        s[i] = char('0' + d);
    }

    // Output the generated counter reading
    println(s);
    return 0;
}
