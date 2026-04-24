#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: weighted towards larger values up to 10, then shift by +2
    int N = rnd.wnext(9, 1) + 2;  // range [2,10]
    // Choose distances, occasionally force them equal for edge cases
    int DA = rnd.next(1, N - 1);
    int DB = rnd.next(1, N - 1);
    if (rnd.next() < 0.2) DB = DA;
    // Choose two distinct starting players A and B
    int A = rnd.next(1, N);
    int B = rnd.next(1, N - 1);
    if (B >= A) ++B;
    // Output in the required format
    println(N, A, B, DA, DB);

    return 0;
}
