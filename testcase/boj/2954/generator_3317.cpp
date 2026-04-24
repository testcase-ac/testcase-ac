#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // vowel and consonant sets
    vector<char> vowels = {'a','e','i','o','u'};
    vector<char> consonants;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (find(vowels.begin(), vowels.end(), c) == vowels.end())
            consonants.push_back(c);
    }
    // Hyper-parameters for diversity
    int W = rnd.next(1, 5);              // number of words
    double vowelProb = rnd.next(0.0, 1.0);
    double consOnlyProb = rnd.next(0.0, 1.0);
    // Build original words
    vector<string> words;
    for (int i = 0; i < W; ++i) {
        int len = rnd.next(1, 5);
        bool consOnly = (rnd.next() < consOnlyProb);
        string w;
        for (int j = 0; j < len; ++j) {
            if (!consOnly && rnd.next() < vowelProb) {
                w += rnd.any(vowels);
            } else {
                w += rnd.any(consonants);
            }
        }
        words.push_back(w);
    }
    // Build original sentence
    string orig;
    for (int i = 0; i < W; ++i) {
        if (i) orig += ' ';
        orig += words[i];
    }
    // Encrypt according to the rule
    string enc;
    for (char c : orig) {
        enc += c;
        if (find(vowels.begin(), vowels.end(), c) != vowels.end()) {
            enc += 'p';
            enc += c;
        }
    }
    // Ensure we do not exceed length limit
    if ((int)enc.size() > 100) {
        // fallback: truncate evenly
        enc = enc.substr(0, 100);
        // avoid trailing 'p' issues: remove trailing incomplete pattern
        while (!enc.empty() && enc.back() == 'p') enc.pop_back();
    }
    // Output encrypted sentence
    println(enc);
    return 0;
}
