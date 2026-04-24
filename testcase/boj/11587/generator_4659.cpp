#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of words
    int N = rnd.next(1, 10);
    // Bias towards smaller maximum word length
    int maxWordLen = rnd.wnext(10, -1);
    maxWordLen = max(1, maxWordLen);

    // Generate dictionary words
    vector<string> words;
    for (int i = 0; i < N; i++) {
        int len = rnd.next(1, maxWordLen);
        string w;
        for (int j = 0; j < len; j++) {
            char c = char('a' + rnd.next(0, 25));
            w.push_back(c);
        }
        words.push_back(w);
    }

    // T9 mapping: a->2, b->2, c->2, d->3, ..., w->9, x->9, y->9, z->9
    const string mp = "22233344455566677778889999";

    // Decide whether to create a matching S or a random S
    bool makeMatch = rnd.next(0, 1) == 1;
    string S;
    if (makeMatch) {
        // Pick a random word and map it to digits
        string w = rnd.any(words);
        for (char c : w) {
            S.push_back(mp[c - 'a']);
        }
    } else {
        // Random digit string of random length
        int sLen = rnd.next(1, maxWordLen);
        for (int i = 0; i < sLen; i++) {
            int d = rnd.next(2, 9);
            S.push_back(char('0' + d));
        }
    }

    // Output the test case
    println(N);
    for (auto &w : words) {
        println(w);
    }
    println(S);

    return 0;
}
