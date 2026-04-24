#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter for N: sometimes minimal, sometimes maximal, else random
        double rN = rnd.next();
        int N;
        if (rN < 0.2) N = 3;
        else if (rN < 0.4) N = 10;
        else N = rnd.next(3, 10);

        // Hyper-parameter for L: ensure L >= 10 and L > N
        int LO = max(N + 1, 10);
        int HI = LO + rnd.next(0, 15);
        int L = rnd.next(LO, HI);

        // Hyper-parameter for k: sometimes 1st, sometimes last, else random
        double rk = rnd.next();
        int k;
        if (rk < 0.2) k = 1;
        else if (rk < 0.4) k = N;
        else k = rnd.next(1, N);

        // Generate N distinct positions in [1, L-1], sorted
        vector<int> posPool;
        posPool.reserve(L - 1);
        for (int x = 1; x < L; x++) posPool.push_back(x);
        shuffle(posPool.begin(), posPool.end());
        posPool.resize(N);
        sort(posPool.begin(), posPool.end());

        // Generate N unique absolute IDs
        int maxAbs = rnd.next(N + 1, N * 20);
        vector<int> idPool(maxAbs);
        for (int i = 0; i < maxAbs; i++) idPool[i] = i + 1;
        shuffle(idPool.begin(), idPool.end());
        idPool.resize(N);

        // Assign random directions (+ or -) with some bias
        double rightProb = rnd.next();
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            int v = idPool[i];
            if (rnd.next() < rightProb) A[i] = v;
            else A[i] = -v;
        }

        // Output this test case
        println(N, L, k);
        for (int i = 0; i < N; i++) {
            println(posPool[i], A[i]);
        }
    }

    return 0;
}
