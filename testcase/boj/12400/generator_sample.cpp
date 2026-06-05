#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int length, int alphabetSize) {
    string word;
    word.reserve(length);
    for (int i = 0; i < length; ++i) {
        word.push_back(char('a' + rnd.next(alphabetSize)));
    }
    return word;
}

string joinWords(const vector<string>& words) {
    string line = words.front();
    for (int i = 1; i < (int)words.size(); ++i) {
        line += ' ';
        line += words[i];
    }
    return line;
}

string makeLine(int mode) {
    int alphabetSize = rnd.next(1, 26);

    if (mode == 0) {
        return randomWord(1, alphabetSize);
    }

    if (mode == 1) {
        return randomWord(rnd.next(2, 30), alphabetSize);
    }

    if (mode == 2) {
        int wordCount = rnd.next(2, 8);
        vector<string> words;
        words.reserve(wordCount);
        for (int i = 0; i < wordCount; ++i) {
            words.push_back(randomWord(rnd.next(1, 10), alphabetSize));
        }
        return joinWords(words);
    }

    if (mode == 3) {
        string line = "abcdefghijklmnopqrstuvwxyz";
        int repeats = rnd.next(1, 3);
        for (int i = 1; i < repeats; ++i) {
            line += ' ';
            line += "abcdefghijklmnopqrstuvwxyz";
        }
        return line;
    }

    int totalLength = rnd.next(60, 100);
    int wordCount = rnd.next(1, min(12, (totalLength + 1) / 2));
    int lettersLeft = totalLength - (wordCount - 1);
    vector<string> words;
    words.reserve(wordCount);
    for (int i = 0; i < wordCount; ++i) {
        int wordsLeft = wordCount - i;
        int len = (i + 1 == wordCount) ? lettersLeft : rnd.next(1, lettersLeft - wordsLeft + 1);
        words.push_back(randomWord(len, alphabetSize));
        lettersLeft -= len;
    }
    return joinWords(words);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 30);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println(makeLine(rnd.next(5)));
    }

    return 0;
}
