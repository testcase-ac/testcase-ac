#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int N;
    if (mode <= 2) {
        N = rnd.next(1, 8);
    } else if (mode <= 5) {
        N = rnd.next(9, 20);
    } else {
        N = rnd.next(35, 50);
    }

    vector<int> A(N);
    int valueMode = rnd.next(0, 3);
    if (valueMode == 0) {
        iota(A.begin(), A.end(), 1);
    } else if (valueMode == 1) {
        for (int i = 0; i < N; ++i) {
            A[i] = (i + 1) * rnd.next(2, 11);
        }
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        for (int x = 1; (int)A.size() < N; ++x) {
            int candidate = 1000 + x;
            if (!binary_search(A.begin(), A.end(), candidate)) {
                A.push_back(candidate);
            }
        }
    } else {
        A = rnd.distinct(N, 1, 1000000);
        sort(A.begin(), A.end());
    }

    if (mode == 0) {
        // Keep ascending order.
    } else if (mode == 1) {
        reverse(A.begin(), A.end());
    } else if (mode == 2) {
        shuffle(A.begin(), A.end());
    } else if (mode == 3) {
        for (int i = 0; i + 1 < N; i += 2) {
            if (rnd.next(0, 1)) {
                swap(A[i], A[i + 1]);
            }
        }
    } else if (mode == 4) {
        int rotations = rnd.next(0, N - 1);
        rotate(A.begin(), A.begin() + rotations, A.end());
    } else if (mode == 5) {
        reverse(A.begin(), A.end());
        int l = rnd.next(0, N - 1);
        int r = rnd.next(l, N - 1);
        reverse(A.begin() + l, A.begin() + r + 1);
    } else {
        shuffle(A.begin(), A.end());
    }

    int maxAdjacentMoves = N * (N - 1) / 2;
    int sMode = rnd.next(0, 5);
    int S;
    if (sMode == 0) {
        S = 0;
    } else if (sMode == 1) {
        S = rnd.next(1, min(5, max(1, maxAdjacentMoves)));
    } else if (sMode == 2) {
        S = rnd.next(0, maxAdjacentMoves);
    } else if (sMode == 3) {
        S = maxAdjacentMoves;
    } else if (sMode == 4) {
        S = rnd.next(maxAdjacentMoves, 1000000);
    } else {
        S = 1000000;
    }

    println(N);
    println(A);
    println(S);
    return 0;
}
