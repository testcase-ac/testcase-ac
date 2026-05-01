#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of strings: small enough to check by hand, sometimes 1 for edge case
    int N = rnd.next(1, 10);
    bool valid;
    if (N == 1) {
        valid = true; // always valid when only one string
    } else {
        valid = rnd.next(0, 1);
    }

    // Alphabet string for random picks
    string alph = "abcdefghijklmnopqrstuvwxyz";

    vector<string> S(N);
    if (valid) {
        // All strings share the same start/end character
        char common = alph[rnd.next(0, 25)];
        for (int i = 0; i < N; i++) {
            // Length bias: negative t -> shorter, positive -> longer
            int t = rnd.next(-2, 2);
            int L = rnd.wnext(10, t) + 1;  // length in [1..10]
            string str(L, ' ');
            str[0] = str[L - 1] = common;
            // Fill inner to form palindrome
            for (int j = 1; j <= (L - 1) / 2; j++) {
                char x = alph[rnd.next(0, 25)];
                str[j] = str[L - 1 - j] = x;
            }
            S[i] = str;
        }
    } else {
        // Invalid case: use at least two distinct start/end characters
        int k = rnd.next(2, min(4, N));
        // pick k distinct letters
        shuffle(alph.begin(), alph.end());
        vector<char> letters(alph.begin(), alph.begin() + k);
        for (int i = 0; i < N; i++) {
            char c;
            if (i == 0) c = letters[0];
            else if (i == 1) c = letters[1];
            else c = letters[rnd.next(0, k - 1)];
            int t = rnd.next(-2, 2);
            int L = rnd.wnext(10, t) + 1;
            string str(L, ' ');
            str[0] = str[L - 1] = c;
            for (int j = 1; j <= (L - 1) / 2; j++) {
                char x = alph[rnd.next(0, 25)];
                str[j] = str[L - 1 - j] = x;
            }
            S[i] = str;
        }
    }

    // Shuffle output order for extra variability
    shuffle(S.begin(), S.end());

    // Output
    println(N);
    println(S);

    return 0;
}
