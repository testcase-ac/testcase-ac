#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose length with bias: sometimes small, sometimes large
    int t = rnd.next(-3, 3);
    int len = rnd.wnext(50, t) + 1;  // 1 to 50

    // Choose generation mode for variability
    // 0: fully random, 1: all '9's, 2: random palindrome (not all 9), 3: all same digit (1-8)
    int mode = rnd.next(0, 3);
    string s(len, '0');

    if (mode == 1) {
        // All 9's
        s = string(len, '9');
    } else if (mode == 3) {
        // All same digit from '1'..'8'
        char c = char('1' + rnd.next(0, 7));
        s = string(len, c);
    } else if (mode == 2) {
        // Palindrome, ensure not all '9'
        int half = len / 2;
        bool odd = (len % 2 == 1);
        // First half
        for (int i = 0; i < half; i++) {
            char c = (i == 0) ? char('1' + rnd.next(0, 8)) : char('0' + rnd.next(0, 9));
            s[i] = c;
            s[len - 1 - i] = c;
        }
        if (odd) {
            // Middle character
            char c = (half == 0)
                     ? char('1' + rnd.next(0, 8))
                     : char('0' + rnd.next(0, 9));
            s[half] = c;
        }
        // If accidentally all '9', force first digit to '1'
        bool all9 = true;
        for (char c : s) if (c != '9') { all9 = false; break; }
        if (all9) s[0] = '1';
    } else {
        // Fully random number
        for (int i = 0; i < len; i++) {
            if (i == 0)
                s[i] = char('1' + rnd.next(0, 8));
            else
                s[i] = char('0' + rnd.next(0, 9));
        }
    }

    // Output the generated number N
    println(s);
    return 0;
}
