#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cards
    int N = rnd.next(1, 20);
    int K = rnd.next(1, N);
    // Helper to generate varied initial and card values
    auto randVal = [&]() {
        if (rnd.next(0, 1) == 0)
            return rnd.next(1, 10);
        else
            return rnd.next(11, 1000000);
    };
    int A0 = randVal();
    int B0 = randVal();
    int C0 = randVal();
    int D0 = randVal();
    // Output header
    println(N, K);
    println(A0, B0, C0, D0);
    // Generate cards with random types and values
    string types = "ABCD";
    for (int i = 0; i < N; i++) {
        char T = rnd.any(types);
        int U = randVal();
        println(T, U);
    }
    return 0;
}
