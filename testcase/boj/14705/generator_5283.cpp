#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of players
    int N = rnd.next(2, 10);
    // Two distinct starting players
    int A = rnd.next(1, N);
    int B = rnd.next(1, N);
    while (B == A) B = rnd.next(1, N);

    // Hyper-parameters to bias toward small/large distances
    int tA = rnd.next(-2, 2);
    int tB = rnd.next(-2, 2);
    // Distances in [1, N-1]
    int DA = rnd.wnext(N-1, tA) + 1;
    int DB = rnd.wnext(N-1, tB) + 1;

    // Output one valid test case
    println(N, A, B, DA, DB);
    return 0;
}
