#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of operators K in [0..9], so N = 2*K+1 in [1..19]
    int K = rnd.next(0, 9);
    int N = 2 * K + 1;

    // Hyper-parameters: weights for operators +, -, *
    int wPlus  = rnd.next(1, 10);
    int wMinus = rnd.next(1, 10);
    int wMul   = rnd.next(1, 10);
    int sumW = wPlus + wMinus + wMul;

    // Hyper-parameter: bias for digits (negative => smaller digits, positive => larger)
    int tBias = rnd.next(-3, 3);

    // Build expression
    string expr;
    expr.reserve(N);
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            // digit 0..9 with bias
            int d = rnd.wnext(10, tBias);
            expr.push_back(char('0' + d));
        } else {
            // operator chosen by weights
            int x = rnd.next(1, sumW);
            if (x <= wPlus) expr.push_back('+');
            else if (x <= wPlus + wMinus) expr.push_back('-');
            else expr.push_back('*');
        }
    }

    // Output
    println(N);
    printf("%s\n", expr.c_str());
    return 0;
}
