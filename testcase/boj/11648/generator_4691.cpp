#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose length n with mixed bias towards small or large
    int n;
    if (rnd.next() < 0.5)
        n = rnd.wnext(9, 1) + 1;   // bias towards larger
    else
        n = rnd.wnext(9, -1) + 1;  // bias towards smaller

    string s;
    // With some probability, generate a repeated-digit number
    if (rnd.next() < 0.2) {
        int d = rnd.next(1, 9);
        s = string(n, char('0' + d));
    } else {
        // hyper-parameters for digit distribution
        double zeroProb = rnd.next(0.0, 1.0);
        double smallProb = rnd.next(0.0, 1.0);
        s.resize(n);
        // First digit must be non-zero
        s[0] = char('1' + rnd.next(0, 8));  // '1'..'9'
        for (int i = 1; i < n; i++) {
            double p = rnd.next();
            if (p < zeroProb) {
                s[i] = '0';
            } else if (p < zeroProb + smallProb) {
                // small digit 1..3
                s[i] = char('1' + rnd.next(0, 2));
            } else {
                // larger digit 4..9
                s[i] = char('4' + rnd.next(0, 5));
            }
        }
    }

    // Output the generated number
    println(s);
    return 0;
}
