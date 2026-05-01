#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Precompute lengths of S(k) until exceeding 1e9
    vector<long long> len;
    len.push_back(3);
    while (len.back() < 1000000000LL) {
        int k = (int)len.size();
        long long next = len.back() * 2 + (k + 3LL);
        len.push_back(next);
    }
    int max_k = (int)len.size() - 1;
    const int MAXN = 1000000000;

    int scenario = rnd.next(0, 3);
    int N = 1;
    if (scenario == 0) {
        // Very small N
        N = rnd.next(1, min(10, MAXN));
    } else if (scenario == 1) {
        // Pick a position in the middle 'm'+'o's segment of some S(k)
        int k = rnd.next(1, max_k);
        int prev = (int)len[k-1];
        int mid_len = k + 3;
        int offset = rnd.next(1, mid_len);
        N = prev + offset;
    } else if (scenario == 2) {
        // Random position within a random S(k)
        int k = rnd.next(0, max_k);
        int upper = (int)min(len[k], (long long)MAXN);
        N = rnd.next(1, upper);
    } else {
        // Very large N near the global limit
        int delta = rnd.next(0, 100);
        int low = max(1, MAXN - delta);
        N = rnd.next(low, MAXN);
    }

    println(N);
    return 0;
}
