#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    int maxDeg = min(M, 3);
    // biases for degree and wage distributions
    vector<int> degBias = {-1, 0, 1};
    vector<int> wageBias = {-1, 0, 1};

    // build assignment possibilities
    vector<vector<pair<int,int>>> E(N+1);
    for (int i = 1; i <= N; i++) {
        int db = rnd.any(degBias);
        // degree in [0..maxDeg], biased
        int deg = rnd.wnext(maxDeg+1, db);
        vector<int> jobs(M);
        iota(jobs.begin(), jobs.end(), 1);
        shuffle(jobs.begin(), jobs.end());
        jobs.resize(deg);
        int wb = rnd.any(wageBias);
        for (int j : jobs) {
            // wage in [0..10000], biased
            int w = rnd.wnext(10001, wb);
            E[i].emplace_back(j, w);
        }
    }

    // output
    println(N, M);
    for (int i = 1; i <= N; i++) {
        int d = E[i].size();
        printf("%d", d);
        for (auto &pr : E[i]) {
            printf(" %d %d", pr.first, pr.second);
        }
        printf("\n");
    }
    return 0;
}
