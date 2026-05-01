#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Define generation types:
    // 0: already sorted
    // 1: fully reversed
    // 2: random permutation
    // 3: almost sorted by a few adjacent swaps
    // 4: one subarray reversed
    // 5: two halves swapped
    int type = rnd.next(0, 5);
    vector<int> minN = {1, 2, 1, 2, 3, 2};
    int N = rnd.next(minN[type], 15);

    // Build initial sorted array 1..N
    vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i + 1;

    if (type == 0) {
        // already sorted
    } else if (type == 1) {
        reverse(A.begin(), A.end());
    } else if (type == 2) {
        shuffle(A.begin(), A.end());
    } else if (type == 3) {
        // perform a few random adjacent swaps
        int maxSwaps = max(1, N/3);
        int swaps = rnd.next(1, maxSwaps);
        for (int i = 0; i < swaps; i++) {
            int pos = rnd.next(1, N-1); // 1-based position for swap i and i+1
            swap(A[pos-1], A[pos]);
        }
    } else if (type == 4) {
        // reverse one continuous segment
        int l = rnd.next(1, N-1);
        int r = rnd.next(l+1, N);
        reverse(A.begin() + (l-1), A.begin() + r);
    } else if (type == 5) {
        // swap two halves
        int mid = N / 2;
        vector<int> B;
        B.insert(B.end(), A.begin() + mid, A.end());
        B.insert(B.end(), A.begin(), A.begin() + mid);
        A.swap(B);
    }

    // Output
    println(N);
    println(A);
    return 0;
}
