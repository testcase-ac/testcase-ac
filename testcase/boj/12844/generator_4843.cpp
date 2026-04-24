#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N
    int N = rnd.next(2, 10);

    // Hyper-parameter for initial A_i upper bound
    vector<int> maxAi_choices = {0, 10, 100000};
    int maxAi = rnd.any(maxAi_choices);

    // Generate initial array
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(0, maxAi);
    }

    // Hyper-parameter for M (number of queries)
    vector<int> m_choices = {
        rnd.next(1, 3),
        rnd.next(5, 10),
        rnd.next(15, 20)
    };
    int M = rnd.any(m_choices);

    // Probability of type-1 query
    double pType1 = rnd.next(0.0, 1.0);

    // Generate queries
    vector<tuple<int,int,int,int>> queries;
    bool hasType2 = false;
    for (int qi = 0; qi < M; qi++) {
        bool isType1 = rnd.next() < pType1;
        int i = rnd.next(0, N-1);
        int j = rnd.next(i, N-1);
        if (isType1) {
            // Hyper-parameter for k in type-1
            vector<int> maxK_choices = {0, 10, 100000};
            int maxK = rnd.any(maxK_choices);
            int k = rnd.next(0, maxK);
            queries.emplace_back(1, i, j, k);
        } else {
            hasType2 = true;
            queries.emplace_back(2, i, j, 0);
        }
    }
    // Ensure at least one type-2
    if (!hasType2) {
        int idx = rnd.next(0, M-1);
        auto &t = queries[idx];
        get<0>(t) = 2;
    }

    // Output
    println(N);
    println(A);
    println(M);
    for (auto &t : queries) {
        int type, i, j, k;
        tie(type, i, j, k) = t;
        if (type == 1) {
            println(1, i, j, k);
        } else {
            println(2, i, j);
        }
    }
    return 0;
}
