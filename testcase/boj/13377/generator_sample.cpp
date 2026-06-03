#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string rotatedWord(int shift) {
    string word = "abcdefghi";
    rotate(word.begin(), word.begin() + shift, word.end());
    return word;
}

string nearSortedWord() {
    string word = "abcdefghi";
    int swaps = rnd.next(1, 4);
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, 7);
        swap(word[pos], word[pos + 1]);
    }
    return word;
}

string randomWord() {
    string word = "abcdefghi";
    shuffle(word.begin(), word.end());
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 4) {
        n = rnd.next(1000, 6000);
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(50, 200);
    } else {
        n = rnd.next(1, 25);
    }

    vector<string> words;
    words.reserve(n);
    for (int i = 0; i < n; ++i) {
        int choice = rnd.next(0, 99);
        if (choice < 12) {
            words.push_back("abcdefghi");
        } else if (choice < 24) {
            words.push_back("ihgfedcba");
        } else if (choice < 46) {
            words.push_back(nearSortedWord());
        } else if (choice < 64) {
            words.push_back(rotatedWord(rnd.next(0, 8)));
        } else if (choice < 82) {
            string word = "ihgfedcba";
            int swaps = rnd.next(1, 4);
            for (int j = 0; j < swaps; ++j) {
                int pos = rnd.next(0, 7);
                swap(word[pos], word[pos + 1]);
            }
            words.push_back(word);
        } else {
            words.push_back(randomWord());
        }
    }

    if (mode == 1) {
        sort(words.begin(), words.end());
    } else if (mode == 2) {
        sort(words.rbegin(), words.rend());
    } else if (mode == 3) {
        shuffle(words.begin(), words.end());
    }

    println(n);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
