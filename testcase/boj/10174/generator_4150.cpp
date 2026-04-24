#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: 1 to 10, slightly biased to larger
    int bias = rnd.next(0, 2);
    int n = rnd.wnext(9, bias) + 1;
    println(n);

    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits  = "0123456789";
    const string punct   = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    const string space   = " ";

    for (int tc = 0; tc < n; tc++) {
        // length bucket for diversity
        double p = rnd.next();
        int len;
        if (p < 0.3) {
            len = rnd.next(1, 4);
        } else if (p < 0.7) {
            len = rnd.next(5, 10);
        } else {
            len = rnd.next(11, 18);
        }

        // decide which kinds of chars to include
        double q = rnd.next();
        string pool = letters;
        if (q < 0.7) pool += digits;
        if (q < 0.5) pool += punct;
        if (q < 0.3) pool += space;

        // decide palindrome or not
        bool makePal = (len == 1) || (rnd.next() < 0.5);
        string s(len, ' ');
        if (makePal) {
            // fill half and mirror exactly
            for (int i = 0; i < (len + 1) / 2; i++) {
                s[i] = rnd.any(pool);
            }
            for (int i = 0; i < len / 2; i++) {
                s[len - 1 - i] = s[i];
            }
        } else {
            // fill all randomly
            for (int i = 0; i < len; i++) {
                s[i] = rnd.any(pool);
            }
            // enforce at least one mismatch in a mirrored pair
            int half = len / 2;
            if (half > 0) {
                int pos = rnd.next(0, half - 1);
                int opp = len - 1 - pos;
                char orig = s[opp];
                char c;
                do {
                    c = rnd.any(pool);
                } while (tolower(c) == tolower(orig));
                s[pos] = c;
            }
        }

        // ensure we don't produce a line of only spaces
        bool hasNonSpace = false;
        for (char c : s) if (c != ' ') { hasNonSpace = true; break; }
        if (!hasNonSpace) {
            // force at least one visible character
            int pos = rnd.next(0, len - 1);
            string visible = letters + digits + punct;
            s[pos] = rnd.any(visible);
            // if palindrome, fix mirror
            int opp = len - 1 - pos;
            if (makePal && pos != opp) {
                s[opp] = s[pos];
            }
        }

        // output the string
        printf("%s\n", s.c_str());
    }

    return 0;
}
