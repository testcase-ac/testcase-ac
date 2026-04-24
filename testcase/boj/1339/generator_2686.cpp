#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N;
    vector<string> words;
    // Occasionally generate the classic single-letter ten-word case
    if (rnd.next() < 0.1) {
        N = 10;
        string letters = "ABCDEFGHIJ";
        for (char c : letters) {
            words.push_back(string(1, c));
        }
    } else {
        N = rnd.next(1, 10);
        // Choose number of distinct letters K between 1 and 10, biased
        int t = rnd.any(vector<int>{-2, 2});
        int K = rnd.wnext(10, t) + 1;  // yields 1..10
        // Build the letter set
        vector<char> alphabet;
        for (char c = 'A'; c <= 'Z'; ++c) alphabet.push_back(c);
        shuffle(alphabet.begin(), alphabet.end());
        alphabet.resize(K);
        // Generate N words
        for (int i = 0; i < N; ++i) {
            int L = rnd.next(1, 8);
            string w;
            if (rnd.next() < 0.2) {
                // repeated letter pattern
                char c = rnd.any(alphabet);
                w = string(L, c);
            } else {
                // random letters
                for (int j = 0; j < L; ++j) {
                    w.push_back(rnd.any(alphabet));
                }
            }
            words.push_back(w);
        }
    }
    // Output
    println(N);
    for (auto &w : words) println(w);
    return 0;
}
