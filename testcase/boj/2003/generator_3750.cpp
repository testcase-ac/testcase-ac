#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N
    int N = rnd.next(1, 10);
    // Maximum element value
    int Vmax = rnd.next(1, 20);

    // Choose distribution type based on Vmax
    // 0 = uniform, 1 = skewed small, 2 = one big element (only if Vmax >= 3)
    int maxDist = (Vmax >= 3 ? 2 : 1);
    int dist = rnd.next(0, maxDist);

    vector<int> A(N);
    if (dist == 0) {
        // Uniform 1..Vmax
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(1, Vmax);
    }
    else if (dist == 1) {
        // Skewed towards smaller values
        for (int i = 0; i < N; i++)
            A[i] = rnd.wnext(Vmax, -1) + 1;
    }
    else {
        // Exactly one big element, others smaller
        int bigPos = rnd.next(0, N - 1);
        // Ensure at least one smaller value exists
        int smallMax = rnd.next(1, Vmax - 1);
        for (int i = 0; i < N; i++) {
            if (i == bigPos)
                A[i] = rnd.next(smallMax + 1, Vmax);
            else
                A[i] = rnd.next(1, smallMax);
        }
    }

    // Compute all subarray sums
    int totalSum = 0;
    for (int x : A) totalSum += x;
    set<int> sums;
    for (int i = 0; i < N; i++) {
        int s = 0;
        for (int j = i; j < N; j++) {
            s += A[j];
            sums.insert(s);
        }
    }

    // Decide target M
    bool pickExisting = rnd.next(0, 1) == 1;
    int M;
    if (pickExisting && !sums.empty()) {
        vector<int> vs(sums.begin(), sums.end());
        M = rnd.any(vs);
    } else {
        // Make M impossible (greater than any subarray sum)
        M = totalSum + rnd.next(1, 5);
    }

    // Output
    println(N, M);
    println(A);

    return 0;
}
