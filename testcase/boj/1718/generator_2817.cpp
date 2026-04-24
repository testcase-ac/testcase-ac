#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Alphabet for random letters
    const string alpha = "abcdefghijklmnopqrstuvwxyz";

    // Hyper-parameter: number of words in plaintext
    int W = rnd.next(1, 5);

    // Build words with weighted lengths
    vector<string> words;
    for (int i = 0; i < W; i++) {
        // t>0 biases to longer words, t<0 to shorter
        int t = rnd.next(0, 1) ? 2 : -2;
        int raw_len = rnd.wnext(6, t); // [0,5]
        int L = raw_len + 1;           // [1,6]
        string w;
        w.reserve(L);
        for (int j = 0; j < L; j++) {
            w.push_back(rnd.any(alpha));
        }
        words.push_back(w);
    }

    // Construct plaintext with single spaces
    string plain;
    for (int i = 0; i < W; i++) {
        if (i) plain.push_back(' ');
        plain += words[i];
    }
    // Optionally add leading/trailing spaces
    if (rnd.next() < 0.3) plain = " " + plain;
    if (rnd.next() < 0.3) plain = plain + " ";

    // Hyper-parameter: key length
    int K = rnd.next(1, 5);
    string key;
    key.reserve(K);
    for (int i = 0; i < K; i++) {
        key.push_back(rnd.any(alpha));
    }

    // Output
    println(plain);
    println(key);

    return 0;
}
