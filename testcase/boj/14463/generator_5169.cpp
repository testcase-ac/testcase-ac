#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cows
    int N = rnd.next(1, 10);
    vector<int> seq;
    seq.reserve(2 * N);

    if (N == 1) {
        // Trivial case
        seq.push_back(1);
        seq.push_back(1);
    } else {
        // Choose generation mode
        // 0: uniform random, 1: disjoint pairs, 2: interleaved pairs, 3: mixed
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            // Uniform random sequence
            for (int i = 1; i <= N; ++i) {
                seq.push_back(i);
                seq.push_back(i);
            }
            shuffle(seq.begin(), seq.end());
        } else if (mode == 1) {
            // Disjoint: i,i,i+1,i+1,...
            for (int i = 1; i <= N; ++i) {
                seq.push_back(i);
                seq.push_back(i);
            }
        } else if (mode == 2) {
            // Fully interleaved: 1,2,...,N,1,2,...,N
            for (int i = 1; i <= N; ++i)
                seq.push_back(i);
            for (int i = 1; i <= N; ++i)
                seq.push_back(i);
        } else {
            // Mixed: first k pairs interleaved, rest disjoint
            int k = rnd.next(1, N-1);
            // Interleaved part
            for (int i = 1; i <= k; ++i)
                seq.push_back(i);
            for (int i = 1; i <= k; ++i)
                seq.push_back(i);
            // Disjoint part
            for (int i = k+1; i <= N; ++i) {
                seq.push_back(i);
                seq.push_back(i);
            }
        }
    }

    // Output format
    println(N);
    for (int x : seq)
        println(x);

    return 0;
}
