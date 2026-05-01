#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We'll generate exactly one test case to keep Pisano period sum <= 500000
    int P = 1;
    // Categories: 0=small [2..10], 1=power of 2 (<=512), 2=power of 5 (<=625),
    // 3=2*5^e (<=250), 4=10^e (<=100), 5=random [2..625]
    vector<int> cats = {0,1,2,3,4,5};
    int cat = rnd.any(cats);

    int m = 2;
    if (cat == 0) {
        // small
        m = rnd.next(2, 10);
    } else if (cat == 1) {
        // 2^e, e in [1..9] => m in [2..512]
        int e = rnd.next(1, 9);
        m = 1 << e;
    } else if (cat == 2) {
        // 5^e, e in [1..4] => m in [5..625]
        int e = rnd.next(1, 4);
        m = 1;
        for (int i = 0; i < e; ++i) m *= 5;
    } else if (cat == 3) {
        // 2 * 5^e, e in [1..3] => m in [10..250]
        int e = rnd.next(1, 3);
        int t = 1;
        for (int i = 0; i < e; ++i) t *= 5;
        m = 2 * t;
    } else if (cat == 4) {
        // 10^e, e in [1..2] => m in [10..100]
        int e = rnd.next(1, 2);
        m = 1;
        for (int i = 0; i < e; ++i) m *= 10;
    } else {
        // random in [2..625]
        m = rnd.next(2, 625);
    }

    // Output: P then lines "1 m"
    println(P);
    println(1, m);

    return 0;
}
