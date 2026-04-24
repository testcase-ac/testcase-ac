#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rounds
    int N = rnd.next(3, 10);

    // Choose a distribution type for diversity
    int distType = rnd.next(0, 4);
    vector<pair<int,int>> pairs;
    pairs.reserve(N);

    if (distType == 0) {
        // 0: uniform random A, B
        for (int i = 0; i < N; i++) {
            int A = rnd.next(1, 99);
            int B = rnd.next(1, 99);
            pairs.emplace_back(A, B);
        }
    }
    else if (distType == 1) {
        // 1: A small, B large
        for (int i = 0; i < N; i++) {
            int A = rnd.next(1, 10);
            int B = rnd.next(50, 99);
            pairs.emplace_back(A, B);
        }
    }
    else if (distType == 2) {
        // 2: A large, B small
        for (int i = 0; i < N; i++) {
            int A = rnd.next(50, 99);
            int B = rnd.next(1, 10);
            pairs.emplace_back(A, B);
        }
    }
    else if (distType == 3) {
        // 3: correlated around a few base values
        int nb = rnd.next(1, 3);
        vector<int> bases(nb);
        for (int i = 0; i < nb; i++)
            bases[i] = rnd.next(1, 99);
        for (int i = 0; i < N; i++) {
            int b = rnd.any(bases);
            int na = rnd.next(0, 10) - 5;
            int nbv = rnd.next(0, 10) - 5;
            int A = min(99, max(1, b + na));
            int B = min(99, max(1, b + nbv));
            pairs.emplace_back(A, B);
        }
    }
    else {
        // 4: few distinct values, many duplicates
        int kA = rnd.next(1, min(N, 4));
        int kB = rnd.next(1, min(N, 4));
        vector<int> As(kA), Bs(kB);
        for (int i = 0; i < kA; i++) As[i] = rnd.next(1, 99);
        for (int i = 0; i < kB; i++) Bs[i] = rnd.next(1, 99);
        for (int i = 0; i < N; i++) {
            int A = rnd.any(As);
            int B = rnd.any(Bs);
            pairs.emplace_back(A, B);
        }
    }

    // Shuffle the rounds to avoid ordered patterns
    shuffle(pairs.begin(), pairs.end());

    // Output
    println(N);
    for (auto &pr : pairs)
        println(pr.first, pr.second);

    return 0;
}
