#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose maximum bit index up to 5 for hand-checkable size
    int maxBit = rnd.next(0, 5);
    vector<int> bitPool;
    for (int i = 0; i <= maxBit; ++i)
        bitPool.push_back(i);

    // Number of required bits N from 0 to bitPool.size()
    int N = rnd.next(0, (int)bitPool.size());
    shuffle(bitPool.begin(), bitPool.end());
    vector<int> bits(bitPool.begin(), bitPool.begin() + N);
    // Shuffle output order of bits
    shuffle(bits.begin(), bits.end());

    // Choose A in [1,10], and sometimes make B < A to test edge case
    int A = rnd.next(1, 10);
    int B;
    if (A > 1 && rnd.next() < 0.2) {
        // 20% chance B < A
        B = rnd.next(1, A - 1);
    } else {
        // Otherwise B between A and 50
        B = rnd.next(A, 50);
    }

    // Output
    println(N, A, B);
    for (int b : bits)
        println(b);

    return 0;
}
