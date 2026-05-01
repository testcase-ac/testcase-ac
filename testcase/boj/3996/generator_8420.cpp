#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    long long n;
    int k;
    int t = rnd.next(0, 3);
    if (t == 0) {
        // small n, small k
        n = rnd.next(1LL, 50LL);
        k = rnd.next(2, 5);
    } else if (t == 1) {
        // medium n, moderate k
        n = rnd.next(1LL, 100000LL);
        k = rnd.next(2, 100);
    } else if (t == 2) {
        // large n, special small k to test edge bases
        n = rnd.wnext(1000000000000000LL, 2);
        vector<int> special = {2, 3, 5, 10, 1000};
        k = rnd.any(special);
    } else {
        // large n, random k
        n = rnd.wnext(1000000000000000LL, 2);
        k = rnd.next(2, 1000);
    }
    println(n, k);
    return 0;
}
