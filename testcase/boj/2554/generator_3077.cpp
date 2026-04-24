#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Three categories for diversity: small, medium-digit, large-digit N
    int category = rnd.next(0, 2);
    string N;

    if (category == 0) {
        // small N between 1 and 20
        int n = rnd.next(1, 20);
        N = to_string(n);
    } else if (category == 1) {
        // medium-digit N: 2 to 4 digits
        int len = rnd.next(2, 4);
        N.resize(len);
        // First digit non-zero
        N[0] = char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; i++) {
            N[i] = char('0' + rnd.next(0, 9));
        }
    } else {
        // large-digit N: 50 to 100 digits
        int len = rnd.next(50, 100);
        N.resize(len);
        // First digit non-zero
        N[0] = char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; i++) {
            N[i] = char('0' + rnd.next(0, 9));
        }
    }

    // Output the single test case
    println(N);
    return 0;
}
