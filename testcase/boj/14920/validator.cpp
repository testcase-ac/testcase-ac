#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the initial term C1
    long long C1 = inf.readLong(1LL, 100000LL, "C(1)");
    inf.readEoln();

    // Global property: for C(1) <= 5*2^60 (and thus <=100000), the Collatz sequence reaches 1.
    // We simulate to ensure the sequence indeed hits 1.
    long long cur = C1;
    int steps = 1;
    const int MAX_STEPS = 1000000;  // generous upper bound for safety
    while (cur != 1 && steps <= MAX_STEPS) {
        if (cur % 2 == 0) {
            cur = cur / 2;
        } else {
            cur = cur * 3 + 1;
        }
        steps++;
    }
    ensuref(cur == 1,
            "Collatz sequence starting at C(1)=%lld did not reach 1 within %d steps",
            C1, MAX_STEPS);

    inf.readEof();
    return 0;
}
