#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

long long lcmLL(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return a / std::gcd(a, b) * b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int Tmax = 100000;

    // Choose scenario for diversity
    int mode = rnd.next(0, 4);
    int N;
    long long B;

    if (mode == 0) {
        // Minimal-like case
        N = 3;
        B = rnd.next(1, 20);
    } else if (mode == 1) {
        // Small N, random B
        N = rnd.next(3, 10);
        B = rnd.next(1, Tmax);
    } else if (mode == 2) {
        // Medium N, random B
        N = rnd.next(10, 40);
        B = rnd.next(1, Tmax);
    } else if (mode == 3) {
        // B as product of small primes
        N = rnd.next(3, 40);
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
        shuffle(primes.begin(), primes.end());
        B = 1;
        for (int p : primes) {
            int maxE = 0;
            while (B * p <= Tmax && maxE < 6) {
                if (rnd.next(0, 1) == 0) break;
                B *= p;
                maxE++;
            }
        }
        if (B == 1) B = 2;
    } else {
        // Prime or prime power
        N = rnd.next(3, 20);
        vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        int p = rnd.any(smallPrimes);
        int e = 1;
        long long val = p;
        // Max exponent so that p^e <= Tmax
        while (val * p <= Tmax && e < 10) {
            if (rnd.next(0, 2) == 0) break;
            val *= p;
            e++;
        }
        B = val;
    }

    // Factor B
    long long tmp = B;
    vector<int> pf;      // primes
    vector<int> pe;      // exponents
    for (long long d = 2; d * d <= tmp; ++d) {
        if (tmp % d == 0) {
            int cnt = 0;
            while (tmp % d == 0) {
                tmp /= d;
                cnt++;
            }
            pf.push_back((int)d);
            pe.push_back(cnt);
        }
    }
    if (tmp > 1) {
        pf.push_back((int)tmp);
        pe.push_back(1);
    }
    int P = (int)pf.size();

    // Exponents for each planet period A_k
    vector< vector<int> > aExp(N, vector<int>(P, 0));

    for (int k = 0; k < N; ++k) {
        for (int j = 0; j < P; ++j) {
            int ej = pe[j];
            int val = 0;
            if (mode == 0) {
                // Bias strongly to small exponents
                val = rnd.wnext(ej + 1, -2);
            } else if (mode == 4) {
                // Bias somewhat to larger exponents
                val = rnd.wnext(ej + 1, 2);
            } else {
                val = rnd.next(0, ej);
            }
            if (val < 0) val = 0;
            if (val > ej) val = ej;
            aExp[k][j] = val;
        }
    }

    // Ensure lcm(A_k) has full exponent for each prime (so overall period's lcm is B)
    for (int j = 0; j < P; ++j) {
        int curMax = 0;
        for (int k = 0; k < N; ++k) {
            curMax = max(curMax, aExp[k][j]);
        }
        if (curMax < pe[j]) {
            int idx = rnd.next(0, N - 1);
            aExp[idx][j] = pe[j];
        }
    }

    // Build A_k from exponents
    vector<long long> A(N, 1);
    for (int k = 0; k < N; ++k) {
        long long v = 1;
        for (int j = 0; j < P; ++j) {
            for (int t = 0; t < aExp[k][j]; ++t) {
                v *= pf[j];
            }
        }
        A[k] = v; // A[k] divides B and thus <= Tmax
    }

    // Compute T_i = lcm of each triple
    vector<long long> T(N - 2);
    for (int i = 0; i <= N - 3; ++i) {
        long long x = lcmLL(A[i], A[i + 1]);
        x = lcmLL(x, A[i + 2]);
        if (x < 1) x = 1;
        if (x > Tmax) x = Tmax; // should not happen, but just in case
        T[i] = x;
    }

    // Output
    println(N);
    println(T);

    return 0;
}
