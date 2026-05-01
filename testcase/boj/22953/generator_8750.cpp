#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K, C;
    vector<int> A;

    int type = rnd.next(0, 6);

    if (type == 0) {
        // Very small random case
        N = rnd.next(1, 3);
        K = rnd.next(1, 20);
        C = rnd.next(0, 5);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, 10);
        }
    } else if (type == 1) {
        // Single cook, possibly very large K and A
        N = 1;
        if (rnd.next(0, 1) == 0)
            K = rnd.next(1, 100);
        else
            K = rnd.next(500000, 1000000);
        C = rnd.next(0, 5);
        A.resize(1);
        A[0] = rnd.next(1, 1000000);
    } else if (type == 2) {
        // Some cooks with time 1, others moderately slow, C > 0
        N = rnd.next(2, 7);
        K = rnd.next(1, 200);
        C = rnd.next(1, 5);
        A.assign(N, 0);
        int ones = rnd.next(1, N - 1);
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < N; i++) {
            if (i < ones) A[idx[i]] = 1;
            else A[idx[i]] = rnd.next(2, 50);
        }
    } else if (type == 3) {
        // All cooks have the same speed
        N = rnd.next(2, 10);
        vector<int> bases = {2, 3, 5, 10, 100, 1000};
        int base = rnd.any(bases);
        K = rnd.wnext(1000000, 3) + 1;
        if (rnd.next(0, 1) == 0) C = 0;
        else C = 5;
        A.assign(N, base);
    } else if (type == 4) {
        // General random case, mix of small and large A
        N = rnd.next(2, 10);
        K = rnd.next(1, 1000000);
        C = rnd.next(0, 5);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            if (rnd.next(0, 2) <= 1) {
                // mostly small values
                A[i] = rnd.next(1, 30);
            } else {
                A[i] = rnd.next(1000, 1000000);
            }
        }
    } else if (type == 5) {
        // Near-extreme values
        N = 10;
        K = 1000000;
        C = 5;
        A.resize(N);
        for (int i = 0; i < 5; i++) {
            A[i] = rnd.next(1, 100);
        }
        for (int i = 5; i < 10; i++) {
            A[i] = rnd.next(500000, 1000000);
        }
        shuffle(A.begin(), A.end());
    } else if (type == 6) {
        // Hand-crafted interesting cases (including samples)
        struct Case {
            int N, K, C;
            vector<int> A;
        };
        vector<Case> cases;

        // Sample 1
        cases.push_back({3, 6, 2, {1, 2, 3}});
        // Sample 2
        cases.push_back({2, 204, 1, {100, 101}});
        // Sample 3
        cases.push_back({2, 200, 1, {100, 101}});
        // Custom cases
        cases.push_back({3, 15, 3, {3, 4, 9}});
        cases.push_back({3, 10, 5, {2, 3, 7}});
        cases.push_back({4, 40, 5, {5, 6, 7, 8}});
        cases.push_back({4, 25, 2, {1, 10, 10, 10}});

        Case tc = rnd.any(cases);
        N = tc.N;
        K = tc.K;
        C = tc.C;
        A = tc.A;
    }

    println(N, K, C);
    println(A);

    return 0;
}
