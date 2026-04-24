#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length
    int N = rnd.next(1, 10);

    // Hyper-parameter for value range diversity
    int low, up;
    double t = rnd.next();
    if (t < 0.33) {
        // Mostly non-positive values
        up = 0;
        low = rnd.next(-1000, 0);
    } else if (t < 0.66) {
        // Mostly non-negative values
        low = 0;
        up = rnd.next(0, 1000);
    } else {
        // Full range
        low = rnd.next(-1000, 1000);
        up = rnd.next(low, 1000);
    }

    // Generate the array
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(low, up);
    }

    // Number of queries
    int M = rnd.next(1, 20);

    // Generate queries with diverse segment lengths
    vector<pair<int,int>> queries;
    for (int q = 0; q < M; q++) {
        if (rnd.next() < 0.3) {
            // Single-element query
            int i = rnd.next(1, N);
            queries.emplace_back(i, i);
        } else {
            // Multi-element query with biased length
            int len;
            if (rnd.next() < 0.5) {
                // bias towards shorter segments
                len = rnd.wnext(N, -1) + 1;
            } else {
                // bias towards longer segments
                len = rnd.wnext(N, 1) + 1;
                if (len > N) len = N;
            }
            int i = rnd.next(1, N - len + 1);
            int j = i + len - 1;
            queries.emplace_back(i, j);
        }
    }

    // Output
    println(N);
    println(A);
    println(M);
    for (auto &p : queries) {
        println(p.first, p.second);
    }

    return 0;
}
