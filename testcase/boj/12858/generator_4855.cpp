#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 10);
    // Hyper-parameters for initial values
    int LB = rnd.next(1, 50);
    int UB = rnd.next(LB, LB + rnd.next(0, 100));
    UB = min(UB, 1000000000);

    // Generate the sequence
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.next(LB, UB);
    }

    // Number of operations
    int Q = rnd.next(1, 20);

    // Build operations, ensuring at least one GCD query
    vector<tuple<int,int,int>> ops;
    for (int i = 0; i < Q - 1; i++) {
        bool isAdd = rnd.next(0.0, 1.0) < 0.6; // 60% chance of add
        int A = rnd.next(1, N);
        int B;
        if (rnd.next(0.0, 1.0) < 0.3)
            B = A;
        else
            B = rnd.next(A, N);
        int T;
        if (isAdd) {
            int tp = rnd.next(0, 2);
            if (tp == 0)
                T = rnd.next(1, 5);
            else if (tp == 1)
                T = rnd.next(1, 1000);
            else
                T = rnd.next(1, 1000000000);
        } else {
            T = 0;
        }
        ops.emplace_back(T, A, B);
    }
    // Ensure at least one GCD query
    {
        int A = rnd.next(1, N);
        int B = (rnd.next(0.0, 1.0) < 0.3 ? A : rnd.next(A, N));
        ops.emplace_back(0, A, B);
    }

    // Output in order
    println(N);
    println(a);
    println(Q);
    for (auto &op : ops) {
        int T, A, B;
        tie(T, A, B) = op;
        println(T, A, B);
    }

    return 0;
}
