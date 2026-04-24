#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total intervals
    int N = rnd.next(2, 12);
    // Length of the main nested chain
    int L = rnd.next(2, N);
    // Base for the chain
    int A0 = rnd.next(5, 10);
    int B0 = rnd.next(A0 + L + 1, A0 + 20);

    vector<pair<int,int>> intervals;
    // Generate a strictly nested main chain
    for (int i = 0; i < L; i++) {
        int dA = rnd.next(0, i);
        int dB = rnd.next(0, i);
        int A = A0 + dA;
        int B = B0 - dB;
        if (B <= A) B = A + 1;
        intervals.emplace_back(A, B);
    }

    // Add distractor intervals
    int D = N - L;
    for (int i = 0; i < D; i++) {
        int A, B;
        int type = rnd.next(0, 2);
        if (type == 0) {
            // Random interval in a broad range
            A = rnd.next(1, B0 + 3);
            B = rnd.next(A + 1, B0 + 5);
        } else if (type == 1) {
            // Overlapping with one in the chain but not fully contained
            auto p = intervals[rnd.next(0, L - 1)];
            if (rnd.next(0, 1) == 0) {
                A = p.first - rnd.next(1, 3);
                B = p.second - rnd.next(0, (p.second - p.first) / 2 + 1);
            } else {
                A = p.first + rnd.next(1, (p.second - p.first) / 2 + 1);
                B = p.second + rnd.next(1, 3);
            }
            if (A < 1) A = 1;
            if (B <= A) B = A + 1;
        } else {
            // Disjoint interval
            if (rnd.next(0, 1) == 0) {
                B = A0 - rnd.next(1, 3);
                A = rnd.next(1, B - 1);
            } else {
                A = B0 + rnd.next(1, 3);
                B = rnd.next(A + 1, A + 5);
            }
        }
        intervals.emplace_back(A, B);
    }

    // Shuffle everything
    shuffle(intervals.begin(), intervals.end());

    // Output
    println(N);
    for (auto &p : intervals) {
        println(p.first, p.second);
    }
    return 0;
}
