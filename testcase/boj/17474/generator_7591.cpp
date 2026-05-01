#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

struct Query {
    int type, L, R;
    long long X;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for small, readable sizes
    int maxN = 20, minM = 2, maxM = 50;
    int biasN = rnd.next(-1, 1);
    int N = rnd.wnext(maxN, biasN) + 1;           // N in [1, maxN]
    int biasM = rnd.next(-1, 1);
    int M = rnd.wnext(maxM - minM + 1, biasM) + minM;  // M in [minM, maxM]

    // Generate initial array A with diverse patterns
    vector<long long> A(N);
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // Uniform random small values
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(0, 100);
    } else if (mode == 1) {
        // Increasing arithmetic sequence
        long long start = rnd.next(0, 50);
        long long delta = rnd.next(0, 5);
        for (int i = 0; i < N; i++)
            A[i] = start + delta * i;
    } else if (mode == 2) {
        // Constant blocks
        int bs = rnd.next(1, max(1, N));
        long long val = rnd.next(0, 100);
        for (int i = 0; i < N; i++) {
            if (i % bs == 0)
                val = rnd.next(0, 100);
            A[i] = val;
        }
    } else {
        // Wider random range
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(0, 500);
    }

    // Helper to pick a random [L, R]
    auto randLR = [&]() {
        int L = rnd.next(1, N);
        int R = rnd.next(L, N);
        return make_pair(L, R);
    };

    // Generate queries, ensuring at least one type-2 and one type-3
    vector<Query> Qs;
    {
        auto p = randLR();
        Qs.push_back({2, p.first, p.second, 0});
    }
    {
        auto p = randLR();
        Qs.push_back({3, p.first, p.second, 0});
    }
    for (int i = 2; i < M; i++) {
        int w = rnd.next(1, 10);
        int t = (w <= 6 ? 1 : (w <= 8 ? 2 : 3));  // bias: 60% type1, 20% type2, 20% type3
        auto p = randLR();
        if (t == 1) {
            long long X = rnd.next(0, 100);
            Qs.push_back({1, p.first, p.second, X});
        } else {
            Qs.push_back({t, p.first, p.second, 0});
        }
    }

    // Shuffle to mix ensured queries
    shuffle(Qs.begin(), Qs.end());

    // Output
    println(N);
    println(A);
    println(M);
    for (auto &q : Qs) {
        if (q.type == 1)
            println(1, q.L, q.R, q.X);
        else
            println(q.type, q.L, q.R);
    }

    return 0;
}
