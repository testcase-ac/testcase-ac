#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with some bias towards small or larger values
    int N_small = rnd.next(1, 9);
    int N_large = rnd.next(10, 20);
    int N = rnd.next(0, 1) ? N_large : N_small;

    // Decide if this should be an impossible case (only if N >= 3)
    bool impossible = false;
    if (N >= 3 && rnd.next(0, 9) < 3) {
        impossible = true;
    }

    vector<int> A(N, 0), B(N, 0);

    if (impossible) {
        // Force a value to appear 3 times total
        int v = rnd.next(1, N);
        // pick 3 distinct positions
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int k = 0; k < 3; k++) {
            int i = idx[k];
            if (rnd.next(0, 1) == 0)
                A[i] = v;
            else
                B[i] = v;
        }
        // fill other entries randomly
        for (int i = 0; i < N; i++) {
            if (A[i] == 0) A[i] = rnd.next(1, N);
            if (B[i] == 0) B[i] = rnd.next(1, N);
        }
    } else {
        // Solvable: ensure no value occurs more than twice by using exactly two copies of each
        vector<int> valList;
        valList.reserve(2 * N);
        for (int v = 1; v <= N; v++) {
            valList.push_back(v);
            valList.push_back(v);
        }
        shuffle(valList.begin(), valList.end());
        for (int i = 0; i < N; i++) {
            A[i] = valList[2*i];
            B[i] = valList[2*i + 1];
        }
    }

    // Output
    println(N);
    println(A);
    println(B);

    return 0;
}
