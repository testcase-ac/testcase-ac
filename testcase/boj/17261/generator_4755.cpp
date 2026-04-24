#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose tree height k (1 <= k <= 4), so N = 2^k - 1 up to 15
    int k = rnd.next(1, 4);
    int N = (1 << k) - 1;
    // Small and large weight bounds
    int smallMax = rnd.next(1, 20);
    int largeMax = rnd.next(smallMax + 1, smallMax * 10);
    double largeProb = rnd.next(); // probability to pick a large weight
    
    vector<int> W(N + 1);
    // Generate weights
    for (int i = 1; i <= N; i++) {
        if (rnd.next() < largeProb) {
            W[i] = rnd.next(smallMax + 1, largeMax);
        } else {
            W[i] = rnd.next(1, smallMax);
        }
    }
    // Ensure at least one leaf has weight 1
    int leafStart = (N + 1) / 2;
    int forcedLeaf = rnd.next(leafStart, N);
    W[forcedLeaf] = 1;
    
    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        printf("%d%c", W[i], i == N ? '\n' : ' ');
    }
    
    return 0;
}
