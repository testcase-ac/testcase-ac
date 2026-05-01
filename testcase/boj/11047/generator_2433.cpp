/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of coin types between 2 and 10
    int N = rnd.next(2, 10);

    // Build a strictly increasing coin system where each coin divides the next
    vector<long long> A;
    A.push_back(1);
    for (int i = 2; i <= N; ++i) {
        long long prev = A.back();
        long long max_factor = 1000000LL / prev;
        if (max_factor < 2) break;

        // Randomly decide whether to grow slowly or quickly
        int bound = (rnd.next() < 0.5 ? 5 : 100);
        int hi = (int)min<long long>(max_factor, bound);
        int factor = rnd.next(2, hi);

        A.push_back(prev * factor);
    }
    N = (int)A.size();

    // Choose K small enough for hand-checking
    long long hiK1 = A.back() * rnd.next(1, 5);
    long long hiK = min(10000LL, hiK1);
    if (hiK < 1) hiK = 1;
    long long K = rnd.next(1LL, hiK);

    // Output in required format
    println(N, K);
    for (auto v : A)
        println(v);

    return 0;
}
