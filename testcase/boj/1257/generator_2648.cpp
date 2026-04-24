/* generator code */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a large M in the valid range, but near the lower bound for hand-checking
    long long M = rnd.next(1000000000LL, 1000001000LL);
    // Small number of coin types
    int N = rnd.next(1, 10);

    vector<int> A;
    // Always include a 1-coin
    A.push_back(1);
    // Generate other coin values
    for (int i = 1; i < N; i++) {
        int coin;
        if (rnd.next() < 0.3) {
            // some larger coins
            coin = rnd.next(1000, 10000);
        } else {
            // smaller but >1 coins
            coin = rnd.next(2, 999);
        }
        A.push_back(coin);
    }
    // Shuffle the coin types
    shuffle(A.begin(), A.end());

    // Output
    println(M);
    println(N);
    for (int x : A) printf("%d ", x);
    printf("\n");
    return 0;
}
