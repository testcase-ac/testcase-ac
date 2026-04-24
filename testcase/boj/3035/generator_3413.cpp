#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable outputs
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);
    int ZR = rnd.next(1, 5);
    int ZC = rnd.next(1, 5);

    // Composition mode: 0 = letters, 1 = digits, 2 = mixed with dots
    int mode = rnd.next(0, 2);
    // Probability of dot in mixed mode
    double pDot = rnd.next(0.0, 1.0);

    // Output header
    println(R, C, ZR, ZC);

    // Generate the newspaper article
    for (int i = 0; i < R; i++) {
        string line;
        line.reserve(C);
        for (int j = 0; j < C; j++) {
            char ch;
            if (mode == 0) {
                // alphabet only
                ch = char('a' + rnd.next(0, 25));
            } else if (mode == 1) {
                // digits only
                ch = char('0' + rnd.next(0, 9));
            } else {
                // mixed: dot vs letter vs digit
                double p = rnd.next();
                if (p < pDot) {
                    ch = '.';
                } else {
                    // half chance letter or digit
                    if (rnd.next() < 0.5)
                        ch = char('a' + rnd.next(0, 25));
                    else
                        ch = char('0' + rnd.next(0, 9));
                }
            }
            line.push_back(ch);
        }
        println(line);
    }

    return 0;
}
