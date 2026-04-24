#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nicknames
    int N = rnd.next(1, 10);
    println(N);

    // Hyper-parameters for diversity
    // Bias parameters for segment count and segment length
    vector<int> biasOptions = {-3, -1, 0, 1, 3};
    int biasSeg = rnd.any(biasOptions);
    int biasLen = rnd.any(biasOptions);
    // Choose a random max character for the nickname letters
    char maxChar = char(rnd.next('c', 'z'));

    for (int i = 0; i < N; i++) {
        // Number of syllables (segments), at least 2
        int segs = rnd.wnext(5, biasSeg) + 2;  // range [2..6]
        vector<string> parts;
        for (int j = 0; j < segs; j++) {
            // Length of this segment
            int len = rnd.wnext(7, biasLen) + 1;  // range [1..8]
            string s;
            for (int k = 0; k < len; k++) {
                char c = char(rnd.next('a', maxChar));
                s.push_back(c);
            }
            parts.push_back(s);
        }
        // Join parts with single space
        string line;
        for (int j = 0; j < (int)parts.size(); j++) {
            if (j) line.push_back(' ');
            line += parts[j];
        }
        // Output the pre-split nickname
        printf("%s\n", line.c_str());
    }

    return 0;
}
