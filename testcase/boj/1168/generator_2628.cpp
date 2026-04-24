#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a small N (1 to 10), biased slightly towards larger values
    int N = rnd.wnext(10, 2) + 1;
    // Generate K between 1 and N
    int K = rnd.next(1, N);

    // Output format: N K
    println(N, K);
    return 0;
}
