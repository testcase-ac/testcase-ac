#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

const string VOWELS = "AEIOU";

string makeWord(char first, char last, int length) {
    if (length == 1) return string(1, first);

    string word;
    word += first;
    for (int i = 2; i < length; ++i) word += rnd.any(VOWELS);
    word += last;
    return word;
}

void addUnique(vector<string>& words, set<string>& seen, char first, char last, int minLen, int maxLen) {
    for (int attempt = 0; attempt < 2000; ++attempt) {
        int length = rnd.next(minLen, maxLen);
        if (length == 1 && first != last) length = 2;

        string word = makeWord(first, last, length);
        if (seen.insert(word).second) {
            words.push_back(word);
            return;
        }
    }

    for (int length = 1; length <= 100; ++length) {
        if (length == 1 && first != last) continue;
        string word = makeWord(first, last, length);
        if (seen.insert(word).second) {
            words.push_back(word);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 16);

    vector<string> words;
    set<string> seen;

    if (mode == 0) {
        n = rnd.next(1, 5);
        char c = rnd.any(VOWELS);
        for (int i = 0; i < n; ++i) {
            int maxLen = (i == n - 1 && rnd.next(0, 3) == 0) ? 100 : 12;
            addUnique(words, seen, c, c, 1, maxLen);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 16);
        char cur = rnd.any(VOWELS);
        for (int i = 0; i < n; ++i) {
            char nxt = rnd.any(VOWELS);
            addUnique(words, seen, cur, nxt, 2, 18);
            cur = nxt;
        }
    } else if (mode == 2) {
        n = rnd.next(5, 16);
        vector<char> cycle;
        int cycleLen = rnd.next(2, 5);
        for (int i = 0; i < cycleLen; ++i) cycle.push_back(VOWELS[i]);
        shuffle(cycle.begin(), cycle.end());

        for (int i = 0; i < n; ++i) {
            char first = cycle[i % cycleLen];
            char last = cycle[(i + 1) % cycleLen];
            int maxLen = rnd.next(0, 5) == 0 ? 100 : 20;
            addUnique(words, seen, first, last, 2, maxLen);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 16);
        for (int i = 0; i < n; ++i) {
            char first = rnd.any(VOWELS);
            char last = rnd.any(VOWELS);
            int minLen = rnd.next(0, 4) == 0 ? 1 : 2;
            int maxLen = rnd.next(0, 6) == 0 ? 100 : 16;
            addUnique(words, seen, first, last, minLen, maxLen);
        }
    } else {
        n = 16;
        for (int i = 0; i < n; ++i) {
            char first = VOWELS[i % 5];
            char last = VOWELS[(i / 5 + i) % 5];
            addUnique(words, seen, first, last, 90, 100);
        }
    }

    shuffle(words.begin(), words.end());

    println((int)words.size());
    for (const string& word : words) println(word);

    return 0;
}
