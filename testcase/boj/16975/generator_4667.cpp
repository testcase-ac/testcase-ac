#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Query {
    int type;
    int i, j, k, x;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);
    int Bmax = rnd.any(vector<int>{10, 100, 1000, 1000000});
    int Kmax = rnd.any(vector<int>{10, 100, 1000, 1000000});
    double p_update = rnd.next(0.0, 1.0);

    // Generate initial array A
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, Bmax);
    }

    // Generate queries
    vector<Query> qs;
    if (M == 1) {
        // Only one, must be a query
        qs.push_back({2, 0, 0, 0, rnd.next(1, N)});
    } else {
        // First M-1 randomly
        for (int it = 0; it < M - 1; it++) {
            if (rnd.next() < p_update) {
                // Type 1 update
                int l = rnd.next(1, N);
                int r = rnd.next(l, N);
                int k;
                if (rnd.next() < 0.5) {
                    k = rnd.next(-Kmax, Kmax);
                } else {
                    // weighted k
                    int t = rnd.any(vector<int>{-2, -1, 1, 2});
                    k = rnd.wnext(2 * Kmax + 1, t) - Kmax;
                }
                qs.push_back({1, l, r, k, 0});
            } else {
                // Type 2 query
                qs.push_back({2, 0, 0, 0, rnd.next(1, N)});
            }
        }
        // Ensure at least one type-2
        qs.push_back({2, 0, 0, 0, rnd.next(1, N)});
    }

    // Output
    println(N);
    println(A);
    println((int)qs.size());
    for (auto &q : qs) {
        if (q.type == 1) {
            println(1, q.i, q.j, q.k);
        } else {
            println(2, q.x);
        }
    }

    return 0;
}
