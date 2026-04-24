#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose N small even number between 2 and 10
    int N = rnd.next(1, 5) * 2;
    // Number of operations, small for hand-checking
    int Q = rnd.next(1, 20);

    // Probability of swap operation
    double swapProb = rnd.next(0.0, 1.0);
    // Bias for selecting which shift operation
    int shiftBias = rnd.next(-2, 2);
    // Biases for selecting rows and columns in swap
    int rowBias = rnd.next(-1, 1);
    int colBias = rnd.next(-1, 1);

    vector<string> shifts = {"RO", "RE", "CO", "CE"};

    // Output N and Q
    println(N, Q);

    for (int i = 0; i < Q; i++) {
        if (rnd.next() < swapProb) {
            // Swap operation S r1 c1 r2 c2
            int r1 = rnd.wnext(N, rowBias) + 1;
            int c1 = rnd.wnext(N, colBias) + 1;
            int r2, c2;
            do {
                r2 = rnd.wnext(N, rowBias) + 1;
                c2 = rnd.wnext(N, colBias) + 1;
            } while (r1 == r2 && c1 == c2);
            println("S", r1, c1, r2, c2);
        } else {
            // One of the four shift operations
            string op = shifts[rnd.wnext(4, shiftBias)];
            println(op);
        }
    }

    return 0;
}
