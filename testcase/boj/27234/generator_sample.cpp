#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        2, 3, 5, 7, 11, 97, 1009, 1000003, 998244353
    };

    int n;
    int mode = rnd.next(6);
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 90);
    } else if (mode == 4) {
        n = rnd.next(91, 149);
    } else {
        n = 150;
    }

    int p = rnd.any(primes);
    println(n, p);

    return 0;
}
