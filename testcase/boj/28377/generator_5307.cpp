#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias small or large via wnext
    int nhyper = rnd.any(vector<int>{-2, 0, 2});
    int N = 1 + rnd.wnext(9, nhyper); // N in [1,10]
    
    // Hyper-parameters for gaps between lily pads
    int maxGapBound = rnd.next(1, 10);
    int gapHyper = rnd.any(vector<int>{-1, 0, 1});
    
    // Generate strictly increasing initial positions x_i
    vector<int> x(N);
    x[0] = rnd.next(1, 5);
    for (int i = 1; i < N; i++) {
        int gap = 1 + rnd.wnext(maxGapBound, gapHyper);
        x[i] = x[i-1] + gap;
    }
    
    // Hyper-parameter for q and jump distribution
    int Q = rnd.next(1, 20);
    int jumpType = rnd.next(0, 1); // 0: uniform, 1: biased to one frog
    vector<int> jumps(Q);
    
    if (jumpType == 0) {
        // uniform picks
        for (int i = 0; i < Q; i++) {
            jumps[i] = rnd.next(1, N);
        }
    } else {
        // biased to a favorite frog
        int fav = rnd.next(1, N);
        for (int i = 0; i < Q; i++) {
            if (rnd.next() < 0.7)
                jumps[i] = fav;
            else
                jumps[i] = rnd.next(1, N);
        }
    }
    
    // Output in the required format
    println(N);
    println(x);
    println(Q);
    for (int idx : jumps)
        println(idx);
    
    return 0;
}
