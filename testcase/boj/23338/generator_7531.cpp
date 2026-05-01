#include "testlib.h"
#include <algorithm>
using namespace std;
typedef long long ll;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const ll LIM = 1000000000000000000LL;
    int scenario = rnd.next(0, 4);
    ll p, q;
    switch (scenario) {
        case 0:
            // Small values
            p = rnd.next(1LL, 100LL);
            q = rnd.next(1LL, p);
            break;
        case 1:
            // p near maximum, q also large
            p = LIM - rnd.next(0LL, 1000LL);
            q = rnd.next(max(1LL, p - 1000LL), p);
            break;
        case 2:
            // Medium-sized values
            p = rnd.next(1000LL, 1000000LL);
            q = rnd.next(1LL, p);
            break;
        case 3:
            // Large random values
            p = rnd.next(LIM / 2, LIM);
            q = rnd.next(1LL, p);
            break;
        case 4:
            // Edge case p == q
            p = rnd.next(1LL, LIM);
            q = p;
            break;
    }
    println(p, q);
    return 0;
}
