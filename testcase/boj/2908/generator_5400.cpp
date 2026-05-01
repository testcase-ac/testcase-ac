#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int digitBias = rnd.next(-1, 1);   // bias for digit size: negative->small digits, positive->large
    int typeBias  = rnd.next(-1, 1);   // bias for number pattern: 0->uniform, 1->palindrome, 2->same-digit

    auto sampleDigit = [&]() {
        // sample in [1,9] with bias
        return rnd.wnext(9, digitBias) + 1;
    };

    auto genNumber = [&]() {
        // t=0: three independent digits
        // t=1: palindrome (d1 d2 d1)
        // t=2: same-digit (d d d)
        int t = rnd.wnext(3, typeBias);
        int d1 = sampleDigit();
        int d2 = sampleDigit();
        int d3 = sampleDigit();
        if (t == 1) d3 = d1;
        if (t == 2) d2 = d1, d3 = d1;
        return d1 * 100 + d2 * 10 + d3;
    };

    int A = genNumber();
    int B;
    do {
        B = genNumber();
    } while (B == A);

    println(A, B);
    return 0;
}
