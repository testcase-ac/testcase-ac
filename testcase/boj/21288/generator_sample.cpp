#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string shuffledAlphabetPrefix(int length) {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shuffle(letters.begin(), letters.end());
    return letters.substr(0, length);
}

string makeDie(int k, const string& preferredLetters) {
    string letters = preferredLetters;
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (letters.find(ch) == string::npos) {
            letters.push_back(ch);
        }
    }
    shuffle(letters.begin(), letters.end());
    return letters.substr(0, k);
}

string constructibleWord(const vector<string>& dice) {
    string word;
    for (const string& die : dice) {
        word.push_back(rnd.any(die));
    }
    shuffle(word.begin(), word.end());
    return word;
}

string randomWord(int n, const string& alphabet) {
    string word;
    for (int i = 0; i < n; ++i) {
        word.push_back(rnd.any(alphabet));
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int k;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, 4);
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(4, 6);
        k = rnd.next(2, 6);
        m = rnd.next(12, 35);
    } else if (mode == 2) {
        n = rnd.next(6, 10);
        k = rnd.next(5, 12);
        m = rnd.next(20, 60);
    } else if (mode == 3) {
        n = rnd.next(10, 13);
        k = rnd.next(8, 20);
        m = rnd.next(25, 80);
    } else {
        n = rnd.next(2, 13);
        k = rnd.next(1, 20);
        m = rnd.next(1, 100);
    }

    string baseAlphabet = shuffledAlphabetPrefix(rnd.next(max(k, 2), 26));
    vector<string> dice;
    dice.reserve(n);

    for (int i = 0; i < n; ++i) {
        string preferred;
        if (mode == 1) {
            preferred = string(1, char('A' + (i % 26)));
        } else if (mode == 2) {
            preferred = baseAlphabet.substr(0, min<int>(baseAlphabet.size(), max(1, k / 2)));
        } else if (mode == 3) {
            preferred = baseAlphabet;
        } else {
            preferred = shuffledAlphabetPrefix(rnd.next(1, min(26, k + 3)));
        }
        dice.push_back(makeDie(k, preferred));
    }

    vector<string> words;
    words.reserve(m);
    string wordAlphabet = baseAlphabet;
    for (const string& die : dice) {
        for (char ch : die) {
            if (wordAlphabet.find(ch) == string::npos) {
                wordAlphabet.push_back(ch);
            }
        }
    }

    while ((int)words.size() < m) {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            words.push_back(constructibleWord(dice));
        } else if (kind == 1) {
            words.push_back(randomWord(n, wordAlphabet));
        } else if (kind == 2) {
            char ch = rnd.any(wordAlphabet);
            words.push_back(string(n, ch));
        } else if (kind == 3) {
            string word = constructibleWord(dice);
            word[rnd.next(n)] = rnd.any(string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
            words.push_back(word);
        } else {
            words.push_back(randomWord(n, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        }
    }

    println(n, k, m);
    for (const string& die : dice) {
        println(die);
    }
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
