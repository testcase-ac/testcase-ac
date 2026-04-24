#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: pick a category of test
    int cat = rnd.next(0, 4);
    long long x = 1, y = 1;
    switch (cat) {
        case 0: {
            // both small
            x = rnd.next(1, 10);
            y = rnd.next(1, 10);
            break;
        }
        case 1: {
            // medium
            x = rnd.next(1, 1000);
            y = rnd.next(1, 1000);
            break;
        }
        case 2: {
            // large values
            x = rnd.next(1000000, 1000000000);
            y = rnd.next(1000000, 1000000000);
            break;
        }
        case 3: {
            // ensure gcd > 1 by a common factor
            int k = rnd.next(2, 20);
            int a = rnd.next(1, 50);
            int b = rnd.next(1, 50);
            x = (long long)k * a;
            y = (long long)k * b;
            break;
        }
        case 4: {
            // one side is 1
            if (rnd.next(0,1) == 0) {
                x = 1;
                y = rnd.next(1, 1000000);
            } else {
                y = 1;
                x = rnd.next(1, 1000000);
            }
            break;
        }
        default: {
            x = rnd.next(1, 100);
            y = rnd.next(1, 100);
        }
    }
    // Randomly swap to avoid always x<=y
    if (rnd.next(0,1)) swap(x, y);
    // Output the test case
    println(x, y);
    return 0;
}
