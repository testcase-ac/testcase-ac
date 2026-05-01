#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n with varied modes: small, medium, large
    int mode = rnd.next(1, 10);
    int n;
    if (mode <= 3) {
        n = rnd.next(1, 5);
    } else if (mode <= 8) {
        n = rnd.next(6, 15);
    } else {
        n = rnd.next(16, 30);
    }

    // Bias for '+' vs '-' to create +^+ or -^- richness
    int b = rnd.next(-2, 2);
    int wPlus  = 1 + max(0, b);
    int wMinus = 1 + max(0, -b);
    int wCaret = 1;
    int totalW = wPlus + wMinus + wCaret;

    // Generate base string
    vector<char> s(n);
    for (int i = 0; i < n; i++) {
        int r = rnd.next(totalW - 1);
        if (r < wPlus) s[i] = '+';
        else if (r < wPlus + wMinus) s[i] = '-';
        else s[i] = '^';
    }

    // Inject explicit patterns to ensure edge cases
    vector<string> pats = {"+^+", "-^-"};
    int inj = rnd.next(0, 2);
    for (int k = 0; k < inj; k++) {
        if (n >= 3) {
            string pat = rnd.any(pats);
            int pos = rnd.next(0, n - 3);
            for (int j = 0; j < 3; j++)
                s[pos + j] = pat[j];
        }
    }

    // Occasionally reverse to test boundary patterns
    if (rnd.next() < 0.2) {
        reverse(s.begin(), s.end());
    }

    // Output the generated string
    string out(s.begin(), s.end());
    println(out);

    return 0;
}
