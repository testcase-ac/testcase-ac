#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for word-length bias
    vector<int> bias = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(bias);

    // Number of words in the text
    int N = rnd.next(1, 10);
    vector<string> words;
    words.reserve(N);
    int w = 0;  // max word length
    int z = 0;  // total chars including spaces

    // Generate words
    for (int i = 0; i < N; i++) {
        int len = 1 + rnd.wnext(10, t); // length between 1 and 10 biased by t
        string s;
        s.reserve(len);
        for (int j = 0; j < len; j++) {
            char c = char('a' + rnd.next(0, 25));
            s.push_back(c);
        }
        words.push_back(s);
        w = max(w, len);
        z += len;
    }
    z += max(0, N - 1); // spaces between words

    // Choose a and b in the valid range [w, z]
    int a = rnd.next(w, z);
    int b = rnd.next(a, z);

    // Assemble the text line
    string text;
    for (int i = 0; i < N; i++) {
        if (i) text.push_back(' ');
        text += words[i];
    }

    // Output
    println(text);
    println(a, b);
    return 0;
}
