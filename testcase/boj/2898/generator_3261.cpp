#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int W = rnd.next(2, 20);       // width
    int L = rnd.next(1, 10);       // length of sequences
    int N = rnd.next(1, 10);       // number of locks

    // how many distinct patterns
    int g = rnd.next(1, min(N, 4));

    // distribute locks among groups
    vector<int> groupCount(g, 1);
    int rem = N - g;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, g - 1);
        groupCount[idx]++;
    }

    // weighted parameters
    int tSum = rnd.next(-2, 2);
    int tTop = rnd.next(-1, 1);

    // generate g base patterns
    vector<pair<vector<int>, vector<int>>> patterns;
    for (int ig = 0; ig < g; ig++) {
        vector<int> top(L), bot(L);
        for (int j = 0; j < L; j++) {
            // sum = top+bottom in [0..W-1], weighted by tSum
            int sum = (tSum == 0 ? rnd.next(0, W-1) : rnd.wnext(W, tSum));
            // choose top in [0..sum], weighted by tTop
            int tv = (tTop == 0 ? rnd.next(0, sum) : rnd.wnext(sum+1, tTop));
            top[j] = tv;
            bot[j] = sum - tv;
        }
        patterns.emplace_back(top, bot);
    }

    // build the full list of locks
    vector<pair<vector<int>, vector<int>>> locks;
    for (int i = 0; i < g; i++) {
        for (int c = 0; c < groupCount[i]; c++) {
            locks.push_back(patterns[i]);
        }
    }
    shuffle(locks.begin(), locks.end());

    // output
    println(W, L, N);
    for (auto &lk : locks) {
        println(lk.first);
        println(lk.second);
    }
    return 0;
}
