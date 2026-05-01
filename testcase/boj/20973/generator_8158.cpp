#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a random cowphabet (a permutation of 'a'..'z')
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    shuffle(alpha.begin(), alpha.end());

    // Choose heard string length skewed towards smaller sizes (1..30)
    int L = rnd.wnext(30, -1) + 1;

    // Choose a pattern type for variability
    int pattern = rnd.next(0, 4);
    string s;
    s.reserve(L);

    if (pattern == 0) {
        // Pure random letters
        for (int i = 0; i < L; i++)
            s.push_back(alpha[rnd.next(0, 25)]);
    } else if (pattern == 1) {
        // Mostly increasing in cowphabet order
        int pos = rnd.next(0, 25);
        for (int i = 0; i < L; i++) {
            if (rnd.next() < 0.8 && pos < 25)
                pos = rnd.next(pos, 25);
            else
                pos = rnd.next(0, 25);
            s.push_back(alpha[pos]);
        }
    } else if (pattern == 2) {
        // Mostly decreasing in cowphabet order
        int pos = rnd.next(0, 25);
        for (int i = 0; i < L; i++) {
            if (rnd.next() < 0.8 && pos > 0)
                pos = rnd.next(0, pos);
            else
                pos = rnd.next(0, 25);
            s.push_back(alpha[pos]);
        }
    } else if (pattern == 3) {
        // Repeated same letter
        char c = alpha[rnd.next(0, 25)];
        s.assign(L, c);
    } else {
        // Blocks of same or random letters
        int blocks = rnd.next(1, min(L, 5));
        int rem = L;
        for (int b = 0; b < blocks; b++) {
            int blen = rnd.next(1, rem - (blocks - b - 1));
            rem -= blen;
            if (rnd.next(0, 1) == 0) {
                // block of identical letters
                char c = alpha[rnd.next(0, 25)];
                for (int i = 0; i < blen; i++) s.push_back(c);
            } else {
                // block of random letters
                for (int i = 0; i < blen; i++)
                    s.push_back(alpha[rnd.next(0, 25)]);
            }
        }
    }

    // Output the test case
    println(alpha);
    println(s);

    return 0;
}
