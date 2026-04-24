#include "testlib.h"
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters:
    // - Length of A and B (separately)
    // - Digits to use (0-9, but we can restrict the range)

    int len_a = rnd.next(1, 2); // Length of A (1 or 2 digits)
    int len_b = rnd.next(1, 2); // Length of B (1 or 2 digits)

    // Ensure A and B are within the constraint (0 < A, B <= 10)
    int a, b;
    if (len_a == 1 && len_b == 1) {
        a = rnd.next(1, 9);
        b = rnd.next(1, 9);
    } else if (len_a == 2 && len_b == 1) {
        a = 10;
        b = rnd.next(1, 9);
    } else if (len_a == 1 && len_b == 2) {
        a = rnd.next(1, 9);
        b = 10;
    } else { // len_a == 2 && len_b == 2
        a = 10;
        b = 10;
    }

    string s = to_string(a) + to_string(b);
    println(s);

    return 0;
}
