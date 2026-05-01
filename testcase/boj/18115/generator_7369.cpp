#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: skewed distribution over [1..15]
    int t = rnd.next(-1, 1);
    int N = rnd.wnext(15, t) + 1;  // rnd.next(15): [0..14], +1 => [1..15]
    vector<int> A(N + 1);
    // Hyper-parameters for operation probabilities
    double p1 = rnd.next(0, 100) / 100.0;
    double p2 = rnd.next(0, 100) / 100.0 * (1 - p1);
    // Generate operations for steps 1 to N-1
    for (int i = 1; i < N; i++) {
        double r = rnd.next();
        if (r < p1) A[i] = 1;
        else if (r < p1 + p2) A[i] = 2;
        else A[i] = 3;
    }
    // Last operation must be 1
    A[N] = 1;
    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        printf("%d" "%c", A[i], i < N ? ' ' : '\n');
    }
    return 0;
}
