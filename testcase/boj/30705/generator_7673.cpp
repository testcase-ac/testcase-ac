#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of buildings N (1 to 12), biased
    int t = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int N = rnd.wnext(12, t) + 1;  // 1..12

    // Hyper-parameter for number of days M (1 to min(5*N,50)), biased
    int Mmax = min(5 * N, 50);
    int t2 = rnd.any(vector<int>{-1, 0, 1});
    int M = rnd.wnext(Mmax, t2) + 1;  // 1..Mmax

    vector<pair<int,int>> intervals;
    intervals.reserve(M);

    for (int i = 0; i < M; i++) {
        int A, B;
        if (N == 1) {
            // Only one building
            A = B = 1;
        } else {
            int typ = rnd.next(1, 4);
            if (typ == 1) {
                // Full-range interval
                A = 1; B = N;
            } else if (typ == 2) {
                // Singleton interval
                A = rnd.next(1, N);
                B = A;
            } else if (typ == 3) {
                // Small interval of length up to N/4
                int lenSmallMax = max(1, N / 4);
                int len = rnd.next(1, lenSmallMax);
                A = rnd.next(1, N - len + 1);
                B = A + len - 1;
            } else {
                // Uniform random interval
                A = rnd.next(1, N);
                B = rnd.next(A, N);
            }
        }
        intervals.emplace_back(A, B);
    }

    // Shuffle days to avoid sorted patterns
    shuffle(intervals.begin(), intervals.end());

    // Output
    println(N, M);
    for (auto &p : intervals) {
        println(p.first, p.second);
    }

    return 0;
}
