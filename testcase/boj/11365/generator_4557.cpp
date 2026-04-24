#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of lines
    int L = rnd.next(1, 5);

    // A small dictionary of words
    vector<string> dict = {
        "Hello", "world", "C++", "OpenAI", "test",
        "generator", "random", "input", "line", "reverse", "code"
    };
    string punct = ".,!?";

    for (int i = 0; i < L; i++) {
        // Number of words in the original message
        int W = rnd.next(1, 5);
        string s;
        for (int j = 0; j < W; j++) {
            string w = rnd.any(dict);
            // With some probability, add punctuation at end of the word
            if (rnd.next() < 0.3) {
                w += rnd.any(punct);
            }
            if (j) s += ' ';
            s += w;
        }
        // Reverse the string to simulate the cipher
        string r = s;
        reverse(r.begin(), r.end());
        println(r);
    }
    // Sentinel
    println("END");
    return 0;
}
