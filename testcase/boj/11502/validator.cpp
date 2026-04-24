#include "testlib.h"
#include <vector>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Precompute primes up to 999
    const int MAXK = 1000;
    vector<bool> is_prime(MAXK, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXK; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXK; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i < MAXK; ++i)
        if (is_prime[i])
            primes.push_back(i);

    // Precompute which odd K<1000 can be written as sum of three primes
    vector<bool> good(MAXK, false);
    int P = (int)primes.size();
    for (int i = 0; i < P; ++i) {
        for (int j = i; j < P; ++j) {
            for (int k = j; k < P; ++k) {
                int s = primes[i] + primes[j] + primes[k];
                if (s < MAXK)
                    good[s] = true;
            }
        }
    }

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        int K = inf.readInt(7, 999, "K");
        inf.readEoln();
        ensuref(K % 2 == 1, "K must be odd, found K=%d at test case %d", K, tc+1);
        // The problem statement asserts every odd K>=7 has a 3-prime decomposition
        ensuref(good[K], "No decomposition into three primes for K=%d at test case %d", K, tc+1);
    }

    inf.readEof();
    return 0;
}
