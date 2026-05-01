#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> cases;

    // Problem samples
    cases.push_back({3, 10});
    cases.push_back({10, 240});
    cases.push_back({12, 364});
    cases.push_back({100, 2351});
    cases.push_back({629, 163547});

    // Edge and special cases
    cases.push_back({0, 1});
    cases.push_back({0, 37});
    cases.push_back({1, 1});
    cases.push_back({1, 1000000000});
    cases.push_back({2, 999999937});     // gcd(2!, odd large) = 1
    cases.push_back({5, 1024});          // partial 2-adic exponent (gcd = 8)
    cases.push_back({6, 720});           // k = n!
    cases.push_back({6, 729});           // 3-power vs 6!
    cases.push_back({7, 5040});          // k = n!
    cases.push_back({10, 2520});         // k < n!, but rich factorisation
    cases.push_back({10, 999983});       // prime > n, gcd = 1
    cases.push_back({20, 1000000000});   // big composite k, moderate n
    cases.push_back({1000, 997});        // n > k, gcd = k
    cases.push_back({1000000000, 999999937}); // extreme n, large prime k

    // Add some randomized diverse extra cases
    int extra = rnd.next(0, 5);
    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(0, 4);
        long long n = 0, k = 1;
        if (type == 0) {
            // small n, small k
            n = rnd.next(0, 20);
            k = rnd.next(1, 40);
        } else if (type == 1) {
            // large n, small k
            n = rnd.next(1000000, 1000000000);
            k = rnd.next(1, 10000);
        } else if (type == 2) {
            // small n, large k
            n = rnd.next(0, 50);
            k = rnd.next(100000000, 1000000000);
        } else if (type == 3) {
            // both general range
            n = rnd.next(0, 1000000000);
            k = rnd.next(1, 1000000000);
        } else if (type == 4) {
            // n near k boundary
            k = rnd.next(1, 1000000000);
            if (rnd.next(0, 1) == 0) {
                // n slightly smaller or equal
                long long delta = rnd.next(0, 5);
                n = k - delta;
                if (n < 0) n = 0;
            } else {
                // n slightly larger or equal
                long long delta = rnd.next(0, 5);
                n = k + delta;
                if (n > 1000000000LL) n = 1000000000LL;
            }
        }
        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());

    for (auto &p : cases)
        println(p.first, p.second);

    return 0;
}
