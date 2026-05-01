#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small tree size for manual verification
    int N = rnd.next(5, 10);
    int Q = rnd.next(N, min(2 * N, 20));
    // Initial color range
    int Cmax = rnd.next(1, min(N, 5));

    // Generate initial colors A_i
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, Cmax);
    }

    // Generate permutation P of size N+1, with P[0]=0
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    vector<int> P(N + 1);
    P[0] = 0;
    for (int i = 0; i < N; i++) {
        P[i + 1] = perm[i];
    }

    // Generate tree with hyper-parameter for shape
    // 0 = chain, 1 = random tree, 2 = star
    int treeType = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // chain: 1-2-3-...-N
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(i - 1, i);
        }
    } else if (treeType == 1) {
        // random parent tree
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    } else {
        // star: all connect to 1
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(1, i);
        }
    }

    // Prepare queries, ensure at least one type-1 and one type-2
    vector<vector<int>> queries;
    queries.push_back({1, rnd.next(1, N)});
    queries.push_back({2, rnd.next(1, N), rnd.next(1, N)});
    int zMax = Cmax + 2;
    for (int i = 2; i < Q; i++) {
        int t = rnd.next(1, 3);
        if (t == 1) {
            queries.push_back({1, rnd.next(1, N)});
        } else if (t == 2) {
            queries.push_back({2, rnd.next(1, N), rnd.next(1, N)});
        } else {
            queries.push_back({3, rnd.next(1, N), rnd.next(1, zMax)});
        }
    }
    // Shuffle queries for variety
    shuffle(queries.begin(), queries.end());

    // Output the test case
    println(N, Q);
    println(A);
    // Output P[1..N]
    vector<int> Pout(N);
    for (int i = 0; i < N; i++) Pout[i] = P[i + 1];
    println(Pout);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    for (auto &q : queries) {
        println(q);
    }

    return 0;
}
