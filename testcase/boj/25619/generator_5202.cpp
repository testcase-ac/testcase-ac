#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes (at least 2 for an edge)
    int N = rnd.next(2, 10);

    // Build all possible edges and pick a random non-empty subset
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
            allEdges.emplace_back(i, j);
    shuffle(allEdges.begin(), allEdges.end());
    int maxM = (int)allEdges.size();
    // Ensure at least one edge to satisfy 1 ≤ M
    int M = rnd.next(1, maxM);
    vector<pair<int,int>> edges(allEdges.begin(), allEdges.begin() + M);

    // Prepare ranges for (a_i, b_i)
    vector<pair<long long,long long>> ranges = {
        {-10LL, 10LL},
        {-100LL, 100LL},
        {-1000000000LL, 1000000000LL}
    };

    // Generate a_i and b_i for each edge with some zeros sprinkled
    vector<long long> A(M), B(M);
    for (int i = 0; i < M; ++i) {
        int r = rnd.next(0, (int)ranges.size() - 1);
        long long lo = ranges[r].first, hi = ranges[r].second;
        A[i] = rnd.next(lo, hi);
        B[i] = rnd.next(lo, hi);
        if (rnd.next(1, 10) == 1) A[i] = 0;
        if (rnd.next(1, 10) == 1) B[i] = 0;
    }

    // Hyper-parameter for T distribution
    long long T;
    int ttype = rnd.next(0, 2);
    if (ttype == 0) {
        T = rnd.next(-20LL, 20LL);
    } else if (ttype == 1) {
        T = rnd.next(-1000LL, 1000LL);
    } else {
        T = rnd.next(-2000000000000000LL, 2000000000000000LL);
    }

    // Output the test case
    println(N, M);
    for (int i = 0; i < M; ++i) {
        println(edges[i].first, edges[i].second, A[i], B[i]);
    }
    println(T);

    return 0;
}
