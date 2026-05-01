#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in varied ranges
    int mode = rnd.next(1, 4);
    int N;
    if (mode == 1) N = rnd.next(2, 4);
    else if (mode == 2) N = rnd.next(5, 10);
    else if (mode == 3) N = rnd.next(11, 20);
    else N = rnd.next(21, 30);

    // Determine number of transfer stations K
    int maxpos = max(0, N - 2);
    int kmode = rnd.next(1, 5);
    int K;
    if (maxpos == 0) {
        K = 0;
    } else if (kmode == 1) {
        K = 0;
    } else if (kmode == 2) {
        K = 1;
    } else if (kmode == 3) {
        K = maxpos;
    } else if (kmode == 4) {
        K = rnd.next(1, max(1, maxpos / 2));
    } else {
        K = rnd.next(0, maxpos);
    }

    // Sample K distinct positions from [2..N-1]
    vector<int> positions;
    for (int i = 2; i <= N - 1; i++) positions.push_back(i);
    shuffle(positions.begin(), positions.end());
    positions.resize(K);
    sort(positions.begin(), positions.end());

    // Build the station info array
    // A[1] and A[N] = 0; A[i]=1 if i in positions
    vector<int> A(N + 1, 0);
    for (int p : positions) {
        A[p] = 1;
    }

    // Output
    println(N);
    vector<int> out(N);
    for (int i = 1; i <= N; i++) {
        out[i - 1] = A[i];
    }
    println(out);

    return 0;
}
