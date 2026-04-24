#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of points
    int N = rnd.next(1, 10);

    // Initial stars A_i
    vector<int> choices = {5, 10, 20, 1000};
    int maxA = rnd.any(choices);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(0, maxA);
    }

    // Number of queries
    int Q = rnd.next(1, 20);

    // Generate queries with a random ratio of type 2
    double p2 = rnd.next();
    vector<vector<int>> qs;
    int c1 = 0, c2 = 0;
    for (int i = 0; i < Q; i++) {
        if (rnd.next() < p2) {
            // type 2 query
            int X = rnd.next(1, N);
            qs.push_back({2, X});
            c2++;
        } else {
            // type 1 query
            int L = rnd.next(1, N);
            int R = rnd.next(L, N);
            qs.push_back({1, L, R});
            c1++;
        }
    }

    // Ensure at least one of each type
    if (c1 == 0) {
        int idx = rnd.next(0, Q - 1);
        int L = rnd.next(1, N);
        int R = rnd.next(L, N);
        qs[idx] = {1, L, R};
    }
    if (c2 == 0) {
        int idx = rnd.next(0, Q - 1);
        int X = rnd.next(1, N);
        qs[idx] = {2, X};
    }

    // Output
    println(N);
    println(A);
    println(Q);
    for (auto &q : qs) {
        if (q[0] == 1)
            println(1, q[1], q[2]);
        else
            println(2, q[1]);
    }

    return 0;
}
