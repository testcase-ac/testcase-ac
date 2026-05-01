#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose number of nodes
    int N = rnd.next(1, 50);
    vector<tuple<int,int,int>> edges;
    // Ensure at least one edge always
    if (N == 1) {
        int extraE = rnd.next(1, 5);
        for (int i = 0; i < extraE; i++) {
            int w = rnd.wnext(100001, rnd.next(-1,1));
            edges.emplace_back(1, 1, w);
        }
    } else {
        // Build a guaranteed path 1->2->...->N
        for (int i = 1; i < N; i++) {
            int w = rnd.wnext(100001, rnd.next(-1,1));
            edges.emplace_back(i, i+1, w);
        }
        // Extra edges hyper-parameter: density switch
        bool dense = rnd.next(0,1);
        int maxExtra = dense ? min(N*N, 2500 - (N-1)) : min(N*N, 100);
        int extraE = rnd.next(0, maxExtra);
        for (int i = 0; i < extraE; i++) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            int w = rnd.wnext(100001, rnd.next(-1,1));
            edges.emplace_back(u, v, w);
        }
    }
    int M = edges.size();
    // Special ability usages C: multiple scales
    long long C;
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        C = 0;
    } else if (mode == 1) {
        int small_max = max(1, N);
        C = rnd.next(1, small_max);
    } else if (mode == 2) {
        int low = max(1, N);
        int high = M * 2;
        C = rnd.next(low, high);
    } else {
        long long low = (long long)M * 2;
        long long high = (long long)M * 100 + 10;
        C = rnd.next(low, high);
    }
    // Shuffle edge order for variability
    shuffle(edges.begin(), edges.end());
    // Output
    println(N, M, C);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    return 0;
}
