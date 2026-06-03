#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string shuffledAlphabetWord(int len, int alphabetSize) {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string word;
    for (int i = 0; i < len; ++i) {
        word += letters[rnd.next(alphabetSize)];
    }
    return word;
}

string descendingWord(int len, int alphabetSize) {
    string word = shuffledAlphabetWord(len, alphabetSize);
    sort(word.begin(), word.end(), greater<char>());
    return word;
}

string nearPermutationBoundary(int len, int alphabetSize) {
    string word = shuffledAlphabetWord(len, alphabetSize);
    sort(word.begin(), word.end());

    int swaps = rnd.next(1, min(4, max(1, len - 1)));
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(len);
        int b = rnd.next(len);
        swap(word[a], word[b]);
    }
    return word;
}

string repeatedBlockWord(int len, int alphabetSize) {
    vector<char> chars;
    for (int i = 0; i < alphabetSize; ++i) {
        chars.push_back(char('A' + rnd.next(26)));
    }

    string word;
    while ((int)word.size() < len) {
        char c = rnd.any(chars);
        int run = rnd.next(1, min(8, len - (int)word.size()));
        word.append(run, c);
    }

    if (rnd.next(2)) {
        shuffle(word.begin(), word.end());
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(6);
        int len;
        if (mode == 0) {
            len = rnd.next(1, 3);
        } else if (mode == 5) {
            len = rnd.next(31, 100);
        } else {
            len = rnd.next(2, 30);
        }

        int alphabetSize = rnd.next(1, min(26, max(1, len)));
        string word;
        if (mode == 0) {
            word = shuffledAlphabetWord(len, alphabetSize);
        } else if (mode == 1) {
            word = descendingWord(len, alphabetSize);
        } else if (mode == 2) {
            word = nearPermutationBoundary(len, alphabetSize);
        } else if (mode == 3) {
            word = repeatedBlockWord(len, rnd.next(1, min(5, alphabetSize)));
        } else if (mode == 4) {
            word = shuffledAlphabetWord(len, rnd.next(2, min(26, alphabetSize + 1)));
        } else {
            word = repeatedBlockWord(len, rnd.next(1, min(8, alphabetSize)));
        }

        println(word);
    }

    return 0;
}
