#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for depth d
    int mode = rnd.next(0, 3);
    int d;
    if (mode == 0) {
        d = 1;
    } else if (mode == 1) {
        d = rnd.next(2, 10);
    } else if (mode == 2) {
        d = rnd.next(11, 25);
    } else {
        d = rnd.next(26, 50);
    }

    // Generate quadrant string with varied patterns
    string digits = "1234";
    string s(d, '1');
    double pat = rnd.next();
    if (pat < 0.2) {
        // all same digit
        char c = rnd.any(digits);
        for (int i = 0; i < d; i++) s[i] = c;
    } else if (pat < 0.4) {
        // alternating two digits
        char c1 = rnd.any(digits), c2 = rnd.any(digits);
        while (c2 == c1) c2 = rnd.any(digits);
        for (int i = 0; i < d; i++) s[i] = (i % 2 ? c1 : c2);
    } else if (pat < 0.6) {
        // repeated prefix
        int len = rnd.next(1, d);
        for (int i = 0; i < len; i++) s[i] = rnd.any(digits);
        for (int i = len; i < d; i++) s[i] = s[i - len];
    } else {
        // fully random
        for (int i = 0; i < d; i++) s[i] = rnd.any(digits);
    }

    // Generate moves x, y with varied magnitudes
    auto genMove = [&](int depth) {
        if (rnd.next() < 0.2) {
            return 0LL;
        }
        if (rnd.next() < 0.5) {
            long long hi = (1LL << depth);
            return rnd.next(-hi, hi);
        } else {
            long long B = (1LL << 50);
            return rnd.next(-B, B);
        }
    };
    long long x = genMove(d);
    long long y = genMove(d);

    // Output the test case
    println(d, s);
    println(x, y);

    return 0;
}
