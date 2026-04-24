#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: skew for length using weighted next
    int weight = rnd.next(-2, 2);
    int maxLen = 12;
    // rnd.wnext(hi, t) samples in [0, hi-1], hi must be >0
    int n = rnd.wnext(maxLen, weight);
    if (n < 1) n = 1;

    // Hyper-parameter: proportion for number of unique characters
    double p = rnd.next();
    int minN26 = min(n, 26);
    int uniq;
    if (n == 1) {
        uniq = 1;
    } else if (n == 2) {
        // For length 2, either 1 or 2 unique letters
        uniq = (p < 0.5 ? 1 : 2);
    } else {
        // For n >= 3, split into three regimes
        if (p < 0.3) {
            uniq = 1;
        } else if (p < 0.6) {
            // pick 2 up to min(n,26)
            uniq = rnd.next(2, minN26);
        } else {
            // pick 3 up to min(n,26)
            uniq = rnd.next(3, minN26);
        }
    }

    // Pick uniq distinct letters from the alphabet
    string alph = "abcdefghijklmnopqrstuvwxyz";
    shuffle(alph.begin(), alph.end());
    vector<char> letters(alph.begin(), alph.begin() + uniq);

    // Hyper-parameter: bias toward using the first letter
    double bias = rnd.next();

    // Build the string S
    string s;
    s.reserve(n);
    for (int i = 0; i < n; i++) {
        if (rnd.next() < bias) {
            s.push_back(letters[0]);
        } else {
            s.push_back(rnd.any(letters));
        }
    }

    // Output the generated word
    printf("%s\n", s.c_str());
    return 0;
}
