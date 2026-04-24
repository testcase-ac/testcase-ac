#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size
    int L = rnd.next(1, 20);

    // Decide generation type
    int type = (L < 2 ? 0 : rnd.next(0, 4));
    string s(L, 'a');

    if (type == 0) {
        // Pure random letters
        for (int i = 0; i < L; i++) {
            s[i] = char('a' + rnd.next(0, 25));
        }
    }
    else if (type == 1) {
        // Random letters over a small alphabet
        int sigma = rnd.next(1, min(5, L));
        for (int i = 0; i < L; i++) {
            s[i] = char('a' + rnd.next(0, sigma - 1));
        }
    }
    else if (type == 2) {
        // Embed two identical blocks
        int b = rnd.next(1, L/2);
        string block;
        for (int i = 0; i < b; i++)
            block += char('a' + rnd.next(0, 25));
        // fill with random
        for (int i = 0; i < L; i++)
            s[i] = char('a' + rnd.next(0, 25));
        int pos1 = rnd.next(0, L - b);
        int pos2 = rnd.next(0, L - b);
        while (pos2 == pos1)
            pos2 = rnd.next(0, L - b);
        for (int i = 0; i < b; i++) {
            s[pos1 + i] = block[i];
            s[pos2 + i] = block[i];
        }
    }
    else if (type == 3) {
        // All same letter (maximal overlapping repeat)
        char c = char('a' + rnd.next(0, 25));
        for (int i = 0; i < L; i++)
            s[i] = c;
    }
    else {
        // Periodic pattern
        int p = rnd.next(1, L);
        vector<char> pat(p);
        for (int i = 0; i < p; i++)
            pat[i] = char('a' + rnd.next(0, 25));
        for (int i = 0; i < L; i++)
            s[i] = pat[i % p];
    }

    // Output
    println(L);
    println(s);
    return 0;
}
