#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeWord(int len, int alphabetSize) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('a' + rnd.next(alphabetSize));
    }
    return s;
}

string shuffledCopy(string s) {
    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 24);
    int alphabetSize = rnd.next(1, 10);
    int maxLen = rnd.next(1, 18);

    vector<string> bases;
    int baseCount = rnd.next(1, min(n, 8));
    for (int i = 0; i < baseCount; ++i) {
        int len = rnd.next(1, maxLen);
        bases.push_back(makeWord(len, alphabetSize));
    }

    vector<string> words;
    while ((int)words.size() < n) {
        if (mode == 0) {
            words.push_back(makeWord(rnd.next(1, maxLen), alphabetSize));
        } else if (mode == 1) {
            words.push_back(shuffledCopy(rnd.any(bases)));
        } else if (mode == 2) {
            string base = rnd.any(bases);
            words.push_back(rnd.next(2) ? base : shuffledCopy(base));
        } else if (mode == 3) {
            int len = rnd.next(1, maxLen);
            string word(len, char('a' + rnd.next(alphabetSize)));
            words.push_back(word);
        } else {
            string base = rnd.any(bases);
            if (rnd.next(3) == 0) {
                words.push_back(base);
            } else {
                words.push_back(shuffledCopy(base));
            }
        }
    }

    println(n);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
