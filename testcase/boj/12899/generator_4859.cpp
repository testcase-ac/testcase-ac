#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Total number of queries
    int N = rnd.next(2, 15);
    // Hyper-parameter: max value for additions, skewed by wnext
    int wparam = rnd.next(-1, 1);
    int maxValue = rnd.wnext(20, wparam) + 1; // in [1,20]

    // Hyper-parameter: number of blocks to vary add/remove probability
    int blockCount = rnd.next(1, min(5, N));
    vector<double> blockProb(blockCount);
    for (int i = 0; i < blockCount; i++) {
        blockProb[i] = rnd.next(); // each block has its own add-probability
    }

    vector<pair<int,int>> queries;
    queries.reserve(N);
    int currSize = 0;

    for (int i = 0; i < N; i++) {
        int blk = (i * blockCount) / N;
        double pAdd = blockProb[blk];
        int T, X;
        if (currSize == 0) {
            T = 1;
        } else {
            // decide type
            if (rnd.next() < pAdd) T = 1;
            else T = 2;
        }
        if (T == 1) {
            X = rnd.next(1, maxValue);
            currSize++;
        } else {
            X = rnd.next(1, currSize);
            currSize--;
        }
        queries.emplace_back(T, X);
    }

    // Ensure at least one removal
    bool hasRemove = false;
    for (auto &q : queries) if (q.first == 2) hasRemove = true;
    if (!hasRemove) {
        // mutate second query into a removal of the smallest
        // after first query currSize was 1
        queries[1] = {2, 1};
    }

    // Output
    println(N);
    for (auto &q : queries) {
        println(q.first, q.second);
    }
    return 0;
}
