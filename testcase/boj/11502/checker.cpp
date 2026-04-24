#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

static const int MAXK = 1000;
vector<bool> is_prime;

// global K for current test
int K;

// Reads an answer (either jury's or participant's) from stream, checks its validity,
// and returns the vector of primes (size 3) or empty vector if "0".
vector<int> readAns(InStream &stream) {
    // Read first integer
    int x = stream.readInt(0, MAXK, "answer");
    vector<int> res;
    if (x == 0) {
        // the "impossible" answer
        return res;
    }
    // otherwise we expect three primes
    res.push_back(x);
    int y = stream.readInt(1, MAXK, "answer");
    int z = stream.readInt(1, MAXK, "answer");
    res.push_back(y);
    res.push_back(z);
    // Check that there is no extra data on this line (optional)
    // stream.readEoln();
    // Check non-decreasing order
    if (!(res[0] <= res[1] && res[1] <= res[2])) {
        stream.quitf(_wa, "numbers are not in non-decreasing order: {%d, %d, %d}", 
                    res[0], res[1], res[2]);
    }
    // Check each is prime
    for (int v : res) {
        if (v < 2 || v > MAXK || !is_prime[v]) {
            stream.quitf(_wa, "%d is not prime", v);
        }
    }
    // Check sum equals K
    int sum = res[0] + res[1] + res[2];
    if (sum != K) {
        stream.quitf(_wa, "sum of primes = %d but expected %d", sum, K);
    }
    return res;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Precompute primes up to MAXK
    is_prime.assign(MAXK+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= MAXK; i++) {
        if (is_prime[i]) {
            for (int j = i*i; j <= MAXK; j += i)
                is_prime[j] = false;
        }
    }

    // Read input
    int T = inf.readInt();
    for (int tc = 0; tc < T; tc++) {
        K = inf.readInt();
        // Read jury and participant answers
        vector<int> want = readAns(ans);
        vector<int> got  = readAns(ouf);
        // Compare
        if (want.size() != got.size()) {
            quitf(_wa, "test %d: expected %s, found %s",
                  tc+1,
                  want.empty() ? "0" : 
                    (to_string(want[0]) + " " + to_string(want[1]) + " " + to_string(want[2])).c_str(),
                  got.empty() ? "0" : 
                    (to_string(got[0])  + " " + to_string(got[1])  + " " + to_string(got[2])).c_str());
        }
        if (!want.empty()) {
            // both size==3
            if (want != got) {
                quitf(_wa, "test %d: expected \"%d %d %d\", found \"%d %d %d\"",
                      tc+1,
                      want[0], want[1], want[2],
                      got[0],  got[1],  got[2]);
            }
        }
        // else both say impossible – OK
    }

    quitf(_ok, "All tests passed");
    return 0;
}
