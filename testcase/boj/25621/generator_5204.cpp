#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: favor small or large
    int tN = rnd.next(0, 1) * 2 - 1;        // -1 or +1
    int N = rnd.wnext(10, tN) + 1;          // in [1..10]

    // Hyper-parameter for initial K0: favor small or large
    int tK = rnd.next(0, 1) * 2 - 1;        // -1 or +1
    int K0 = rnd.wnext(21, tK);             // in [0..20]

    println(N, K0);

    // Function to choose an operation string
    auto chooseOp = [&]() {
        // pick operator uniformly
        char op = rnd.any(string("+-*"));

        // hyper-parameter for x: favor extremes or middle
        int tX = rnd.next(0, 1) * 2 - 1;     // -1 or +1
        int x;
        if (op == '*') {
            // x in [0..10]
            x = rnd.wnext(11, tX);
        } else {
            // x in [0..20]
            x = rnd.wnext(21, tX);
        }
        return string(1, op) + to_string(x);
    };

    // Generate the N lines, each with two operations
    for (int i = 0; i < N; i++) {
        string op1 = chooseOp();
        string op2 = chooseOp();
        println(op1, op2);
    }

    return 0;
}
