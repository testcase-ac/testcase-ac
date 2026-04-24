#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 7);
    // Weighted choice for M to get small or large sequences sometimes
    int t = rnd.next(-1, 1);
    int M = rnd.wnext(N, t) + 1;

    // Choose a small value range hyper-parameter
    int V = rnd.any(vector<int>{5, 10, 20});

    // Generate the array of N numbers, with possibility of duplicates
    vector<int> a;
    double distinctModeProb = 0.4;
    if (rnd.next() < distinctModeProb && V >= N) {
        // Generate N distinct values
        vector<int> pool(V);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        pool.resize(N);
        a = pool;
    } else {
        // Generate a smaller base set and allow repeats
        int D = rnd.next(1, min(N, V));
        vector<int> pool(V);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        pool.resize(D);
        for (int i = 0; i < N; i++) {
            a.push_back(rnd.any(pool));
        }
    }

    // Finally shuffle the input order
    shuffle(a.begin(), a.end());

    // Output
    println(N, M);
    println(a);

    return 0;
}
