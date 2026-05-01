#include "testlib.h"
#include <numeric>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mode = rnd.next(0, 6);
    ll a, b, S;
    switch (mode) {
        // small random
        case 0:
            a = rnd.next(1, 10);
            b = rnd.next(1, 10);
            S = rnd.next(0, 100);
            break;
        // medium random
        case 1:
            a = rnd.next(1, 1000);
            b = rnd.next(1, 1000);
            S = rnd.next(0, 10000);
            break;
        // large random
        case 2: {
            const ll MINL = 1000000000000LL;
            const ll MAXL = 1000000000000000000LL;
            a = rnd.next(MINL, MAXL);
            b = rnd.next(MINL, MAXL);
            S = rnd.next(0LL, MAXL);
            break;
        }
        // equal a == b
        case 3:
            a = rnd.next(1, 20);
            b = a;
            S = (ll)rnd.next(0, 20) * a;
            break;
        // gcd > 1
        case 4: {
            ll g = rnd.next(2, 10);
            ll x = rnd.next(1, 20);
            ll y = rnd.next(1, 20);
            a = g * x;
            b = g * y;
            S = (ll)rnd.next(0, 50) * g;
            break;
        }
        // coprime a, b
        case 5:
            do {
                a = rnd.next(1, 50);
                b = rnd.next(1, 50);
            } while (std::gcd(a, b) != 1);
            S = rnd.next(0, 100);
            break;
        // one zero
        case 6:
            if (rnd.next(0,1) == 0) {
                a = 0;
                b = rnd.next(1, 1000);
            } else {
                a = rnd.next(1, 1000);
                b = 0;
            }
            S = rnd.next(0, 1000);
            break;
        default:
            a = 1; b = 1; S = 1;
    }
    println(a, b, S);
    return 0;
}
