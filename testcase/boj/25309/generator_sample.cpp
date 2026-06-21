#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int N = 1;
    int K = 1;

    if (mode == 0) {
        vector<pair<int, int>> edges = {
            {1, 1}, {2, 1}, {3, 2}, {4, 2}, {5, 3}, {7, 4}, {8, 3}
        };
        auto tc = rnd.any(edges);
        N = tc.first;
        K = tc.second;
    } else if (mode == 1) {
        K = 1;
        if (rnd.next(0, 1) == 0) {
            vector<int> primes = {2, 3, 5, 7, 11, 97, 99991};
            N = rnd.any(primes);
        } else {
            vector<int> composites = {1, 4, 6, 9, 25, 100, 100000000};
            N = rnd.any(composites);
        }
    } else if (mode == 2) {
        K = 2;
        if (rnd.next(0, 1) == 0) {
            N = rnd.next(1, 8);
        } else {
            N = rnd.next(4, 100000000);
        }
    } else if (mode == 3) {
        K = rnd.next(3, 20);
        int parity = rnd.next(0, 1);
        int minPossible = (K - 2) * 2 + (parity ? 1 : 2);
        int delta = rnd.next(-3, 12);
        N = minPossible + delta;
        if (N < 1) N = 1;
        if ((N & 1) != parity && N < 100000000) ++N;
    } else if (mode == 4) {
        K = rnd.next(100, 10000);
        int minOdd = (K - 2) * 2 + 1;
        int minEven = (K - 2) * 2 + 2;
        int base = rnd.next(0, 1) ? minOdd : minEven;
        N = base + rnd.next(0, 2000);
        if (N > 100000000) N = 100000000 - rnd.next(0, 1000);
    } else if (mode == 5) {
        K = rnd.next(1, 10000);
        N = rnd.next(99900000, 100000000);
    } else {
        K = rnd.next(1, 10000);
        N = rnd.next(1, 100000000);
    }

    println(N, K);
    return 0;
}
