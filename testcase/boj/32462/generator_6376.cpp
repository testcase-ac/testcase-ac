#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Mandatory small N
    vector<ll> mand = {1,2,3,4,5,6,7};
    set<ll> used(mand.begin(), mand.end());
    int extra = rnd.next(3, 10);
    int T = mand.size() + extra;
    vector<ll> Ns = mand;
    // Some special values
    vector<ll> fib = {
        8,13,21,34,55,89,144,233,377,610,
        987,1597,2584,4181,6765,10946,17711,
        28657,46368,75025,121393,196418,317811,
        514229,832040
    };
    while ((int)Ns.size() < T) {
        double p = rnd.next();
        ll N = 1;
        if (p < 0.10) {
            N = rnd.next(8LL, 50LL);
        } else if (p < 0.20) {
            N = rnd.next(51LL, 500LL);
        } else if (p < 0.30) {
            N = rnd.next(501LL, 10000LL);
        } else if (p < 0.40) {
            N = rnd.next(10001LL, 1000000LL);
        } else if (p < 0.50) {
            N = rnd.next(1000001LL, 1000000000LL - 10);
        } else if (p < 0.60) {
            int e = rnd.next(4, 29);
            N = (1LL << e);
        } else if (p < 0.75) {
            N = rnd.any(fib);
        } else {
            N = 1000000000LL - rnd.next(0, 10);
        }
        if (N < 1 || N > 1000000000LL) continue;
        if (used.insert(N).second) {
            Ns.push_back(N);
        }
    }
    shuffle(Ns.begin(), Ns.end());
    println((int)Ns.size());
    for (ll x : Ns) println(x);
    return 0;
}
