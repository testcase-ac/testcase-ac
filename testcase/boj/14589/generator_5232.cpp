#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of segments
    int N = rnd.next(2, 10);
    // Coordinate range
    int minC = rnd.next(-20, 0);
    int maxC = rnd.next(1, 20);
    int d = maxC - minC;
    int half = d / 2;
    // Probability to generate longer segments
    double longProb = rnd.next();
    // Generate segments
    vector<pair<int,int>> seg(N);
    for (int i = 0; i < N; i++) {
        int len;
        if (rnd.next() < longProb) {
            // longer half-range
            len = rnd.next(half + 1, d);
        } else {
            // shorter half-range
            len = rnd.next(0, half);
        }
        int L = rnd.next(minC, maxC - len);
        seg[i] = {L, L + len};
    }
    // Generate queries
    int maxPairs = N * (N - 1) / 2;
    int Q = rnd.next(1, min(20, maxPairs));
    vector<pair<int,int>> all;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            all.emplace_back(i, j);
    shuffle(all.begin(), all.end());
    // Output
    println(N);
    for (auto &p : seg) println(p.first, p.second);
    println(Q);
    for (int i = 0; i < Q; i++)
        println(all[i].first, all[i].second);
    return 0;
}
