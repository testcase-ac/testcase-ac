#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K, A, B;
    int scenario = rnd.next(0, 6); // 0..6

    auto chooseRandomDivisorLessThanN = [&](int n) -> int {
        vector<int> divs;
        for (int d = 1; d < n; ++d)
            if (n % d == 0)
                divs.push_back(d);
        return rnd.any(divs);
    };

    if (scenario == 0) {
        // Smallest N, unique (A,B) pair
        N = 2;
        A = 1;
        B = 1;           // A*B = 1 < 2
        K = rnd.next(1, 5);
    } else if (scenario == 1) {
        // Small N, balanced divisors (often A = N/2 or 1)
        N = rnd.next(3, 10);
        if (N % 2 == 0 && rnd.next(0, 1) == 0)
            A = N / 2;
        else
            A = 1;
        int maxB = (N - 1) / A;
        B = rnd.next(1, maxB);
        K = rnd.next(1, 10);
    } else if (scenario == 2) {
        // Medium N, A = 1, large B (strong watering on short segment)
        N = rnd.next(10, 30);
        A = 1;
        int maxB = N - 1;
        B = 1 + rnd.wnext(maxB, 3); // bias towards large B
        K = rnd.next(1, 100);
    } else if (scenario == 3) {
        // Medium/Large N, large A, small B
        N = rnd.next(10, 50);
        // Try to pick a divisor > 1, otherwise fall back to 1
        vector<int> bigDivs;
        for (int d = 2; d < N; ++d)
            if (N % d == 0)
                bigDivs.push_back(d);
        if (!bigDivs.empty())
            A = rnd.any(bigDivs);
        else
            A = 1;
        int maxB = (N - 1) / A;
        B = 1 + rnd.wnext(maxB, -3); // bias towards small B
        K = rnd.next(1, 20);
    } else if (scenario == 4) {
        // Near-maximal A*B (borderline constraint)
        N = rnd.next(20, 100);
        A = chooseRandomDivisorLessThanN(N);
        int maxB = (N - 1) / A;
        B = maxB; // A*B = N-1, as large as allowed
        K = rnd.next(1, 100);
    } else if (scenario == 5) {
        // Fully random but with K biased to extremes
        N = rnd.next(2, 100);
        A = chooseRandomDivisorLessThanN(N);
        {
            int maxB = (N - 1) / A;
            B = rnd.next(1, maxB);
        }
        int kType = rnd.next(0, 9);
        if (kType < 5)       // 50% very small K
            K = rnd.next(1, 5);
        else if (kType < 8)  // 30% medium K
            K = rnd.next(6, 20);
        else                 // 20% large K
            K = rnd.next(21, 100);
    } else { // scenario == 6
        // Large K, random others
        N = rnd.next(2, 100);
        A = chooseRandomDivisorLessThanN(N);
        {
            int maxB = (N - 1) / A;
            B = rnd.next(1, maxB);
        }
        K = 100;
    }

    // Final safety: ensure constraints hold
    if (!(2 <= N && N <= 100)) return 0;
    if (!(1 <= K && K <= 100)) return 0;
    if (!(1 <= A && A <= N && N % A == 0)) return 0;
    if (!(1 <= B)) return 0;
    if (!(1LL * A * B < N)) return 0;

    vector<int> out = {N, K, A, B};
    println(out);

    return 0;
}
