#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAXV = 1000;
    vector<bool> is_composite(MAXV+1, false);
    is_composite[0] = is_composite[1] = true;
    for (int i = 2; i*i <= MAXV; ++i)
        if (!is_composite[i])
            for (int j = i*i; j <= MAXV; j += i)
                is_composite[j] = true;
    vector<long long> primes;
    for (int i = 2; i <= MAXV; ++i)
        if (!is_composite[i])
            primes.push_back(i);
    // twin low: p where p+2 is prime; twin high: q where q-2 is prime
    vector<long long> twin_low, twin_high, residual;
    for (long long p : primes) {
        bool low = !is_composite[p+2];
        bool high = (p-2>=2 && !is_composite[p-2]);
        if (low) twin_low.push_back(p);
        if (high) twin_high.push_back(p);
    }
    // residual: primes not 2, not twin_low, not twin_high, and >20 to avoid small clusters
    for (long long p : primes) {
        if (p <= 20) continue;
        bool low = !is_composite[p+2];
        bool high = (p-2>=2 && !is_composite[p-2]);
        if (!low && !high) residual.push_back(p);
    }
    // decide case: 0=direct twin, 1=via 2 (3-step), 2=impossible
    int t = rnd.next(0, 2);
    long long A, B;
    if (t == 0 && !twin_low.empty()) {
        // direct twin
        long long p = rnd.any(twin_low);
        long long q = p + 2;
        if (rnd.next(0,1)) { A = p; B = q; }
        else { A = q; B = p; }
    } else if (t == 1 && !twin_low.empty()) {
        // via 2 in three steps: path exists only if other is twin_low
        long long p = rnd.any(twin_low);
        if (rnd.next(0,1)) { A = 2; B = p; }
        else { A = p; B = 2; }
    } else {
        // impossible
        if (residual.size() < 2) {
            // fallback to some non-twin pair
            vector<long long> cand;
            for (long long p : primes)
                if (p != 2 && (is_composite[p+2] || p+2 > MAXV) 
                    && (p-2 < 2 || is_composite[p-2]))
                    cand.push_back(p);
            residual = cand;
        }
        // ensure we have at least 2
        long long p = rnd.any(residual);
        long long q;
        do { q = rnd.any(residual); } while (q == p);
        A = p; B = q;
    }
    println(A, B);
    return 0;
}
