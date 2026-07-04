#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string randomLowerWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) {
        word.push_back(static_cast<char>('a' + rnd.next(26)));
    }
    return word;
}

string randomCapitalizedWord(int minLen, int maxLen) {
    string word = randomLowerWord(minLen, maxLen);
    word[0] = static_cast<char>('A' + rnd.next(26));
    return word;
}

void appendCapped(string& text, const string& chunk, int targetLength) {
    int remaining = targetLength - static_cast<int>(text.size());
    if (remaining <= 0) return;
    text.append(chunk.substr(0, remaining));
}

void appendEnglishLike(string& text, int targetLength) {
    const vector<string> common = {
        "the", "of", "for", "and", "to", "in", "is", "on", "that", "by",
        "this", "with", "you", "from", "as", "was", "her", "his", "they",
        "their", "book", "room", "morning", "quiet", "thought"
    };
    const vector<string> punctuation = {". ", ", ", "; ", ": ", "? ", "! "};

    while (static_cast<int>(text.size()) < targetLength) {
        int wordsInSentence = rnd.next(6, 18);
        appendCapped(text, randomCapitalizedWord(3, 9), targetLength);
        for (int i = 1; i < wordsInSentence; ++i) {
            appendCapped(text, " ", targetLength);
            if (rnd.next(100) < 72) {
                appendCapped(text, rnd.any(common), targetLength);
            } else {
                appendCapped(text, randomLowerWord(3, 10), targetLength);
            }
            if (rnd.next(100) < 10 && i + 1 < wordsInSentence) {
                appendCapped(text, ",", targetLength);
            }
        }
        appendCapped(text, rnd.any(punctuation), targetLength);
        if (rnd.next(100) < 12) appendCapped(text, "\n", targetLength);
    }
}

void appendRandomWords(string& text, int targetLength) {
    const vector<string> separators = {" ", " ", " ", "\n", ". ", ", ", "   "};

    while (static_cast<int>(text.size()) < targetLength) {
        string word;
        if (rnd.next(100) < 10) {
            word = randomCapitalizedWord(1, 12);
        } else {
            word = randomLowerWord(1, 14);
        }
        appendCapped(text, word, targetLength);
        appendCapped(text, rnd.any(separators), targetLength);
    }
}

void appendPunctuationHeavy(string& text, int targetLength) {
    const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string punctuation = " .,!?:;-'\"()[]";

    while (static_cast<int>(text.size()) < targetLength) {
        int segmentLength = rnd.next(1, 24);
        for (int i = 0; i < segmentLength; ++i) {
            if (rnd.next(100) < 58) {
                appendCapped(text, string(1, rnd.any(alphabet)), targetLength);
            } else {
                appendCapped(text, string(1, rnd.any(punctuation)), targetLength);
            }
        }
        appendCapped(text, rnd.next(100) < 20 ? "\n" : " ", targetLength);
    }
}

void appendLineHeavy(string& text, int targetLength) {
    while (static_cast<int>(text.size()) < targetLength) {
        int lineLength = rnd.next(20, 120);
        for (int i = 0; i < lineLength; ++i) {
            int roll = rnd.next(100);
            if (roll < 70) {
                appendCapped(text, string(1, static_cast<char>('a' + rnd.next(26))), targetLength);
            } else if (roll < 88) {
                appendCapped(text, " ", targetLength);
            } else {
                appendCapped(text, string(1, static_cast<char>('0' + rnd.next(10))), targetLength);
            }
        }
        appendCapped(text, "\n", targetLength);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int targetLength = rnd.next(10000, 18000);
    int mode = rnd.next(4);
    string text;
    text.reserve(targetLength);

    if (mode == 0) {
        appendEnglishLike(text, targetLength);
    } else if (mode == 1) {
        appendRandomWords(text, targetLength);
    } else if (mode == 2) {
        appendPunctuationHeavy(text, targetLength);
    } else {
        appendLineHeavy(text, targetLength);
    }

    cout << text;
    return 0;
}
