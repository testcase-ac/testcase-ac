#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for maximum B
    vector<long long> Bchoices = {100LL, 1000LL, 10000LL};
    long long maxB = rnd.any(Bchoices);

    // Choose A and B in [1, maxB]
    long long A = rnd.next(1LL, maxB / 2LL);
    long long B = rnd.next(A, maxB);

    // Choose X: sometimes force X > B for zero-result edge
    long long X;
    if (rnd.next() < 0.3) {
        // X strictly greater than B
        X = rnd.next(B + 1LL, maxB * 2LL);
    } else {
        X = rnd.next(1LL, B);
    }

    // Build allowed digits: pick a random subset of [0-9]
    vector<char> pool;
    for (char c = '0'; c <= '9'; ++c)
        pool.push_back(c);
    shuffle(pool.begin(), pool.end());
    int dcount = rnd.next(1, 5);
    vector<char> pick(pool.begin(), pool.begin() + dcount);
    sort(pick.begin(), pick.end());

    // Output
    println(X, A, B);
    string s(pick.begin(), pick.end());
    printf("%s\n", s.c_str());

    return 0;
}
