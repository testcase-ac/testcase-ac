#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    double largeNprob = 0.2, cycleProb = 0.2;
    bool makeCycle = rnd.next() < cycleProb;
    int N;
    if (rnd.next() < largeNprob) {
        N = rnd.next(20, 50);
    } else {
        N = rnd.next(2, 10);
    }
    int maxM = min(N, 8);
    int M;
    if (makeCycle) {
        M = rnd.next(2, maxM);
    } else {
        M = rnd.next(1, maxM);
    }

    vector<vector<int>> pds;

    if (makeCycle) {
        // create a small cycle
        int clen = rnd.next(2, min(N, 5));
        vector<int> all(N);
        for (int i = 0; i < N; i++) all[i] = i+1;
        shuffle(all.begin(), all.end());
        vector<int> cycleNodes(all.begin(), all.begin() + clen);
        // PD1: forward cycle
        pds.push_back(cycleNodes);
        // PD2: reverse sequence
        vector<int> rev = cycleNodes;
        reverse(rev.begin(), rev.end());
        pds.push_back(rev);
    }

    // generate remaining PDs
    for (int i = (int)pds.size(); i < M; i++) {
        // biased to shorter sequences
        int k = rnd.wnext(N, -2) + 1;
        if (k > N) k = N;
        vector<int> pool(N);
        for (int j = 0; j < N; j++) pool[j] = j+1;
        shuffle(pool.begin(), pool.end());
        pool.resize(k);
        pds.push_back(pool);
    }

    // shuffle order of PDs for variability
    shuffle(pds.begin(), pds.end());

    // output
    println(N, M);
    for (auto &seq : pds) {
        int k = seq.size();
        printf("%d", k);
        for (int x : seq) printf(" %d", x);
        printf("\n");
    }

    return 0;
}
