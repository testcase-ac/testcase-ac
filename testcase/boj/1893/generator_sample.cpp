#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeAlphabet(int len) {
    string symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    shuffle(symbols.begin(), symbols.end());
    return symbols.substr(0, len);
}

char shifted(char c, const string& alphabet, int shift) {
    int pos = int(alphabet.find(c));
    return alphabet[(pos + shift) % int(alphabet.size())];
}

string shiftString(const string& s, const string& alphabet, int shift) {
    string result = s;
    for (char& c : result) {
        c = shifted(c, alphabet, shift);
    }
    return result;
}

string randomString(const string& alphabet, int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string nonMatchingFiller(const string& alphabet, const string& word, int len) {
    string s;
    int guard = 0;
    do {
        s = randomString(alphabet, len);
        ++guard;
    } while (s.find(word) != string::npos && guard < 200);

    if (s.find(word) != string::npos) {
        char replacement = alphabet[0] == word[0] ? alphabet[1] : alphabet[0];
        for (char& c : s) c = replacement;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(12, 24);
    println(cases);

    for (int tc = 0; tc < cases; ++tc) {
        int alphabetLen = rnd.next(3, 12);
        string alphabet = makeAlphabet(alphabetLen);

        int wordLen = rnd.next(1, 8);
        if (tc % 5 == 0) wordLen = rnd.next(1, 3);
        string word = randomString(alphabet, wordLen);

        int mode = tc % 6;
        string encrypted;

        if (mode == 0) {
            int shift = rnd.next(0, alphabetLen - 1);
            string plain = nonMatchingFiller(alphabet, word, rnd.next(max(3, wordLen), 18));
            int pos = rnd.next(0, int(plain.size()));
            plain.insert(pos, word);
            encrypted = shiftString(plain, alphabet, shift);
        } else if (mode == 1) {
            int repeat = rnd.next(2, 5);
            string plain;
            for (int i = 0; i < repeat; ++i) plain += word;
            encrypted = shiftString(plain, alphabet, rnd.next(0, alphabetLen - 1));
        } else if (mode == 2) {
            int len = rnd.next(max(3, wordLen + 1), 20);
            encrypted = nonMatchingFiller(alphabet, word, len);
        } else if (mode == 3) {
            string base = randomString(alphabet, rnd.next(1, 4));
            word = base + base;
            string plain = base + word + base;
            encrypted = shiftString(plain, alphabet, rnd.next(0, alphabetLen - 1));
        } else if (mode == 4) {
            int shiftA = rnd.next(0, alphabetLen - 1);
            int shiftB = rnd.next(0, alphabetLen - 1);
            string plainA = nonMatchingFiller(alphabet, word, rnd.next(3, 8)) + word;
            string plainB = word + nonMatchingFiller(alphabet, word, rnd.next(3, 8));
            encrypted = shiftString(plainA, alphabet, shiftA);
            encrypted += shiftString(plainB, alphabet, shiftB);
        } else {
            string pattern = randomString(alphabet, rnd.next(2, 5));
            int repeat = rnd.next(2, 6);
            string plain;
            for (int i = 0; i < repeat; ++i) plain += pattern;
            int pos = rnd.next(0, max(0, int(plain.size()) - wordLen));
            plain.replace(pos, wordLen, word);
            encrypted = shiftString(plain, alphabet, rnd.next(0, alphabetLen - 1));
        }

        if (encrypted.size() < 3) {
            encrypted += randomString(alphabet, 3 - int(encrypted.size()));
        }

        println(alphabet);
        println(word);
        println(encrypted);
    }

    return 0;
}
