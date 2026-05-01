#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXN = 1000000000LL;

    int mode = rnd.next(0, 2);

    if (mode == 0) {
        // Very small, easy-to-check tests
        int T = rnd.next(1, 5);
        vector<long long> Ns;

        // Ensure at least one very small N (1, 2, or 3)
        vector<long long> tiny = {1, 2, 3};
        Ns.push_back(rnd.any(tiny));

        while ((int)Ns.size() < T) {
            int type = rnd.next(0, 3);
            long long N;
            if (type == 0) {
                N = rnd.next(1, 10);
            } else if (type == 1) {
                N = rnd.next(1, 30);
            } else if (type == 2) {
                N = rnd.next(1, 100);
            } else {
                N = rnd.next(1, 1000);
            }
            Ns.push_back(N);
        }

        shuffle(Ns.begin(), Ns.end());
        println(T);
        for (long long x : Ns) println(x);
        return 0;
    }

    // More diverse, mixed-size tests
    vector<long long> tests;

    // Always include very small consecutive Ns to see local patterns
    for (int i = 1; i <= 10; i++)
        tests.push_back(i);

    // Optionally extend small consecutive region
    if (rnd.next(0, 1)) {
        for (int i = 11; i <= 15; i++)
            tests.push_back(i);
    }

    // Extreme large values
    tests.push_back(MAXN);
    tests.push_back(MAXN - 1);
    tests.push_back(MAXN - 2);

    // Middle of the range and neighbors
    long long mid = MAXN / 2;
    tests.push_back(mid);
    if (mid - 1 >= 1) tests.push_back(mid - 1);
    if (mid + 1 <= MAXN) tests.push_back(mid + 1);

    // Some random extra special values
    int extra = rnd.next(3, 10);
    for (int i = 0; i < extra; i++) {
        int type = rnd.next(0, 3);
        long long N;
        if (type == 0) {
            // Small range
            N = rnd.next(1, 30);
        } else if (type == 1) {
            // Medium range
            N = rnd.next(31, 1000);
        } else if (type == 2) {
            // Near powers of two
            int k = rnd.next(1, 29);
            long long base = 1LL << k;
            int d = rnd.next(-3, 3);
            long long cand = base + d;
            if (cand < 1) cand = 1;
            if (cand > MAXN) cand = MAXN;
            N = cand;
        } else {
            // Completely random in full range
            N = rnd.next(1LL, MAXN);
        }
        tests.push_back(N);
    }

    // Optionally add a short consecutive block somewhere in the small range
    if (rnd.next(0, 1)) {
        int len = rnd.next(3, 7);
        int start = rnd.next(1, max(1, 50 - len));
        for (int i = 0; i < len; i++)
            tests.push_back(start + i);
    }

    // Shuffle to avoid ordered patterns
    shuffle(tests.begin(), tests.end());

    int T = (int)tests.size();
    if (T > 100) T = 100; // safety guard, though we should be far below this

    println(T);
    for (int i = 0; i < T; i++)
        println(tests[i]);

    return 0;
}
