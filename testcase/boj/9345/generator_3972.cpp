#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    
    for (int tc = 0; tc < T; tc++) {
        // Small N and K
        int N = rnd.next(1, 10);
        int maxK = min(20, N * 5);
        int K = rnd.next(1, maxK);
        println(N, K);
        
        // Hyper-parameters for diversity
        double pSwap   = rnd.next(0.0, 1.0);   // probability of swap event
        int    swapBias  = rnd.next(-2, 2);    // bias for swap indices
        int    queryBias = rnd.next(-2, 2);    // bias for query indices
        
        for (int i = 0; i < K; i++) {
            bool isSwap = rnd.next() < pSwap;
            int Q = isSwap ? 0 : 1;
            // pick indices with bias, then enforce A <= B
            int a = rnd.wnext(N, isSwap ? swapBias : queryBias);
            int b = rnd.wnext(N, isSwap ? swapBias : queryBias);
            if (a > b) swap(a, b);
            println(Q, a, b);
        }
    }
    
    return 0;
}
