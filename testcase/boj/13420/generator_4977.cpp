#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    // Probability of a wrong answer
    double wrongProb = rnd.next(0.0, 1.0);
    // Operator choices
    vector<char> ops = {'+', '-', '*', '/'};
    // Hyper-parameter for operand magnitude
    vector<int> maxChoices = {10, 20, 50};
    int maxAbs = rnd.any(maxChoices);
    // Output number of test cases
    println(T);
    for (int i = 0; i < T; i++) {
        // Choose an operator
        char op = rnd.any(ops);
        long long a, b;
        if (op == '/') {
            // Ensure non-zero divisor
            do {
                b = rnd.next(-maxAbs, maxAbs);
            } while (b == 0);
            // Make dividend divisible by divisor
            long long k = rnd.next(-maxAbs, maxAbs);
            a = b * k;
        } else {
            a = rnd.next(-maxAbs, maxAbs);
            b = rnd.next(-maxAbs, maxAbs);
        }
        // Compute correct result
        long long correct;
        if (op == '+') correct = a + b;
        else if (op == '-') correct = a - b;
        else if (op == '*') correct = a * b;
        else correct = a / b;
        // Possibly make it wrong
        long long c;
        if (rnd.next() < wrongProb) {
            long long delta;
            do {
                delta = rnd.next(-5LL, 5LL);
            } while (delta == 0);
            c = correct + delta;
        } else {
            c = correct;
        }
        // Print the test case
        printf("%lld %c %lld = %lld\n", a, op, b, c);
    }
    return 0;
}
