#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<string> tests;
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    vector<char> fullAlpha(alpha.begin(), alpha.end());

    for (int ti = 0; ti < T; ti++) {
        bool isPangram = rnd.next(0, 1) == 1;
        vector<char> letters = fullAlpha;
        vector<string> words;

        if (isPangram) {
            // Create a true pangram
            shuffle(letters.begin(), letters.end());
            int K = rnd.next(1, 5);
            vector<int> sizes(K, 1);
            int extra = 26 - K;
            for (int i = 0; i < extra; i++)
                sizes[rnd.next(0, K - 1)]++;
            int idx = 0;
            for (int i = 0; i < K; i++) {
                string w;
                for (int j = 0; j < sizes[i]; j++)
                    w += letters[idx++];
                words.push_back(w);
            }
            // Optional filler words
            int add = rnd.next(0, 2);
            for (int i = 0; i < add; i++) {
                int L = rnd.next(1, 5);
                string w;
                for (int j = 0; j < L; j++)
                    w += rnd.any(fullAlpha);
                words.push_back(w);
            }
        } else {
            // Create a non-pangram by omitting some letters
            shuffle(letters.begin(), letters.end());
            int miss = rnd.next(1, min(5, 25));
            vector<char> rem(letters.begin() + miss, letters.end());
            shuffle(rem.begin(), rem.end());
            int remCnt = rem.size();
            int K = rnd.next(1, min(5, remCnt));
            vector<int> sizes(K, 1);
            int extra = remCnt - K;
            for (int i = 0; i < extra; i++)
                sizes[rnd.next(0, K - 1)]++;
            int idx = 0;
            for (int i = 0; i < K; i++) {
                string w;
                for (int j = 0; j < sizes[i]; j++)
                    w += rem[idx++];
                words.push_back(w);
            }
            // Optional filler words not including missing letters
            int add = rnd.next(0, 2);
            for (int i = 0; i < add; i++) {
                int L = rnd.next(1, 5);
                string w;
                for (int j = 0; j < L; j++)
                    w += rnd.any(rem);
                words.push_back(w);
            }
        }

        // Shuffle word order and build sentence
        shuffle(words.begin(), words.end());
        string line;
        for (int i = 0; i < (int)words.size(); i++) {
            if (i) line += ' ';
            line += words[i];
        }
        tests.push_back(line);
    }

    // Output all test cases, ending with *
    for (auto &s : tests)
        println(s);
    println("*");

    return 0;
}
