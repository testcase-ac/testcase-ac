#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter for number of words: biased small or large
        int biasW = rnd.next(-2, 2);
        int W = rnd.wnext(10, biasW) + 1; // ensures [1,10] words

        vector<string> words;
        words.reserve(W);

        for (int i = 0; i < W; ++i) {
            // Hyper-parameter for word length bias
            int biasL = rnd.next(-1, 1);
            int L = rnd.wnext(20, biasL) + 1; // ensures [1,20] characters

            string w;
            w.reserve(L);
            for (int j = 0; j < L; ++j) {
                // pick a lowercase letter
                char c = rnd.any(string("abcdefghijklmnopqrstuvwxyz"));
                // occasionally uppercase
                if (rnd.next(0, 9) == 0) c = char(toupper(c));
                w.push_back(c);
            }
            words.push_back(w);
        }

        // Build and output the sentence
        string sentence = words[0];
        for (int i = 1; i < W; ++i) {
            sentence += ' ';
            sentence += words[i];
        }
        println(sentence);
    }

    return 0;
}
