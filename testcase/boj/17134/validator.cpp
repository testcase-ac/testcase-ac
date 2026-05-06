#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>
using namespace std;

bool is_odd(int n) {
    return n % 2 == 1;
}

bool is_prime(int n, const vector<bool>& is_prime_sieve) {
    if (n < 2) return false;
    return is_prime_sieve[n];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 1000000;
    // Precompute primes up to N_MAX for fast checking
    vector<bool> is_prime_sieve(N_MAX + 1, true);
    is_prime_sieve[0] = is_prime_sieve[1] = false;
    for (int i = 2; i * i <= N_MAX; ++i) {
        if (is_prime_sieve[i]) {
            for (int j = i * i; j <= N_MAX; j += i) {
                is_prime_sieve[j] = false;
            }
        }
    }

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Read N as token to check for leading zeros and numeric format
        string Nstr = inf.readToken("[0-9]+", "N");
        // No leading zeros allowed
        ensuref(Nstr.size() == 1 || Nstr[0] != '0', "N has leading zeros at test case %d: '%s'", tc+1, Nstr.c_str());
        // Convert to int
        ensuref(Nstr.size() <= 7, "N is too large at test case %d: '%s'", tc+1, Nstr.c_str());
        int N = 0;
        for (char c : Nstr) {
            ensuref(isdigit(c), "N contains non-digit character at test case %d: '%s'", tc+1, Nstr.c_str());
            N = N * 10 + (c - '0');
        }
        ensuref(N > 5, "N must be greater than 5 at test case %d: %d", tc+1, N);
        ensuref(N <= N_MAX, "N must be at most %d at test case %d: %d", N_MAX, tc+1, N);
        ensuref(is_odd(N), "N must be odd at test case %d: %d", tc+1, N);

        inf.readEoln();

        // Validate global property: For all N, the answer always exists (i.e., at least one representation exists)
        // We must check that for this N, there is at least one way to write N = odd prime + even semiprime

        // Odd primes: 3, 5, 7, ..., N-4 (since semiprime >= 4)
        bool found = false;
        for (int p = 3; p < N; p += 2) {
            if (!is_prime(p, is_prime_sieve)) continue;
            int s = N - p;
            // s must be even, >= 4, and semiprime (product of two primes)
            if (s < 4 || s % 2 != 0) continue;
            // Check if s is semiprime: s = x * y, x <= y, both primes, x >= 2
            for (int x = 2; x * x <= s; ++x) {
                if (!is_prime(x, is_prime_sieve)) continue;
                if (s % x != 0) continue;
                int y = s / x;
                if (y < x) continue; // ensure x <= y
                if (!is_prime(y, is_prime_sieve)) continue;
                found = true;
                break;
            }
            if (found) break;
        }
        ensuref(found, "No representation for N=%d at test case %d", N, tc+1);
    }

    inf.readEof();
}
