#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Query {
    int type, i, j, k;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of the array
    int N = rnd.next(1, 10);

    // Generate initial array with values in [1,50]
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.next(1, 50);
    }
    vector<int> a0 = a; // keep the original for output

    // Hyper-parameter: number of queries
    int M = rnd.next(1, 20);

    // Hyper-parameter: probability of a type-1 query
    double type1Prob = 0.2 + rnd.next() * 0.6; // in [0.2,0.8)

    vector<Query> qs;
    qs.reserve(M);
    int type1count = 0;

    // Track current maximum to generate k
    int curMax = *max_element(a.begin(), a.end());

    for (int qi = 0; qi < M; qi++) {
        if (rnd.next() < type1Prob) {
            // Type-1 query: count elements > k in [i,j]
            int i = rnd.next(1, N);
            int j = rnd.next(i, N);
            int k;
            // Hyper-parameter: small vs large k
            if (rnd.next() < 0.7) {
                // small k in [1, curMax]
                k = rnd.next(1, curMax);
            } else {
                // large k in [curMax+1, curMax+10]
                k = rnd.next(curMax + 1, curMax + 10);
            }
            qs.push_back({1, i, j, k});
            type1count++;
        } else {
            // Type-2 query: point update A[i] = k
            int i = rnd.next(1, N);
            int newVal = rnd.next(1, 50);
            a[i-1] = newVal;
            curMax = max(curMax, newVal);
            qs.push_back({2, i, 0, newVal});
        }
    }

    // Ensure at least one type-1 query
    if (type1count == 0) {
        int i = rnd.next(1, N);
        int j = rnd.next(i, N);
        int k = rnd.next(1, curMax + 5);
        qs.back() = {1, i, j, k};
    }

    // Output
    println(N);
    println(a0);
    println(M);
    for (auto &q : qs) {
        if (q.type == 1) {
            println(1, q.i, q.j, q.k);
        } else {
            println(2, q.i, q.k);
        }
    }

    return 0;
}
