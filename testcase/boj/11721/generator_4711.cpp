#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide length N, biased towards small or large, with occasional exact 10
    int N;
    if (rnd.next(0, 4) == 0) {
        N = 10;
    } else {
        int bias = rnd.next(-2, 2);
        N = rnd.wnext(20, bias) + 1;  // yields in [1,20]
    }

    // Decide case mode: 0=all lower, 1=all upper, 2=mixed
    int mode = rnd.next(0, 2);
    double mixProb = 0.0;
    if (mode == 2) {
        mixProb = rnd.next(0.0, 1.0);
    }

    // Build the string
    string s;
    s.reserve(N);
    for (int i = 0; i < N; i++) {
        int idx = rnd.next(0, 25);
        char c = char('a' + idx);
        if (mode == 1) {
            c = char(toupper(c));
        } else if (mode == 2 && rnd.next() < mixProb) {
            c = char(toupper(c));
        }
        s.push_back(c);
    }

    // Output the test case
    println(s);
    return 0;
}
