#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N small enough to verify by hand, but varied
    int N = rnd.next(1, 20);
    // Maximum deliciousness
    int maxA = rnd.next(1, 1000);
    if (maxA < 2) maxA = 2;
    vector<long long> A(N);
    // Choose a pattern for variability
    int pat = rnd.next(0, 4);
    switch (pat) {
        case 0:
            // Uniform random
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, maxA);
            break;
        case 1:
            // Alternating high/low
            {
                int lowMax = maxA / 2;
                if (lowMax < 1) lowMax = 1;
                int highMin = lowMax + 1;
                for (int i = 0; i < N; i++) {
                    if (i % 2 == 0)
                        A[i] = rnd.next(1, lowMax);
                    else
                        A[i] = rnd.next(highMin, maxA);
                }
            }
            break;
        case 2:
            // Plateau: K positions high, rest low
            {
                int half = maxA / 2;
                if (half < 1) half = 1;
                int K = rnd.next(1, N);
                vector<int> idx(N);
                iota(idx.begin(), idx.end(), 0);
                shuffle(idx.begin(), idx.end());
                for (int t = 0; t < N; t++) {
                    int i = idx[t];
                    if (t < K)
                        A[i] = rnd.next(half + 1, maxA);
                    else
                        A[i] = rnd.next(1, half);
                }
            }
            break;
        case 3:
            // Two random peaks
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, maxA);
            if (N >= 1) {
                int p1 = rnd.next(0, N - 1);
                A[p1] += maxA; // big peak
            }
            if (N >= 2) {
                int p2 = rnd.next(0, N - 1);
                A[p2] += maxA / 2; // medium peak
            }
            break;
        case 4:
            // Sorted increasing
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, maxA);
            sort(A.begin(), A.end());
            break;
    }
    // Output
    println(N);
    for (auto v : A) println(v);
    return 0;
}
