#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string repeatChar(int n, char c) {
    return string(n, c);
}

string alternating(int n, string alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += alphabet[i % (int)alphabet.size()];
    }
    return s;
}

string randomWord(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string shuffledBlocks(int n, const string& alphabet) {
    vector<string> blocks;
    int remaining = n;
    while (remaining > 0) {
        int len = rnd.next(1, min(remaining, 8));
        blocks.push_back(repeatChar(len, rnd.any(alphabet)));
        remaining -= len;
    }
    shuffle(blocks.begin(), blocks.end());

    string s;
    s.reserve(n);
    for (const string& block : blocks) {
        s += block;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    vector<string> words;
    words.reserve(t);

    words.push_back(string(1, char('a' + rnd.next(26))));
    words.push_back(repeatChar(rnd.next(2, 20), char('a' + rnd.next(26))));
    words.push_back(alternating(rnd.next(2, 25), rnd.next(2) == 0 ? "ab" : "abc"));

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int rampLength = rnd.next(3, 26);
    words.push_back(alphabet.substr(0, rampLength));

    while ((int)words.size() < t) {
        int mode = rnd.next(4);
        int n = rnd.next(1, 60);
        int k = rnd.next(1, 8);
        string letters = alphabet.substr(0, k);
        shuffle(letters.begin(), letters.end());

        if (mode == 0) {
            words.push_back(randomWord(n, letters.substr(0, rnd.next(1, k))));
        } else if (mode == 1) {
            words.push_back(alternating(n, letters.substr(0, rnd.next(1, min(k, 4)))));
        } else if (mode == 2) {
            words.push_back(shuffledBlocks(n, letters));
        } else {
            int prefix = rnd.next(0, n);
            string s = repeatChar(prefix, rnd.any(letters));
            s += randomWord(n - prefix, letters);
            words.push_back(s);
        }
    }

    shuffle(words.begin(), words.end());

    println((int)words.size());
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
