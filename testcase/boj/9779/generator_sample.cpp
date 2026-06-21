#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string randomLetters(int length) {
    string word;
    word.reserve(length);
    for (int i = 0; i < length; ++i) {
        word += char('a' + rnd.next(26));
    }
    return word;
}

string matchingWord() {
    string word = "d";
    word += string(rnd.next(1, 16), 'a');
    word += 'd';
    if (rnd.next(2) == 1) {
        word += 'd';
    }
    word += rnd.next(2) == 0 ? 'i' : 'y';
    return word;
}

string nearMissWord() {
    int mode = rnd.next(6);
    if (mode == 0) return "d" + string(rnd.next(1, 17), 'a');
    if (mode == 1) return "d" + string(rnd.next(1, 16), 'a') + "dd";
    if (mode == 2) return "d" + string(rnd.next(1, 16), 'a') + "dz";
    if (mode == 3) return "d" + string(rnd.next(1, 15), 'a') + "ddz";
    if (mode == 4) return string(rnd.next(1, 18), 'a') + "di";
    return "dd" + string(rnd.next(1, 16), 'a') + "dy";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int wordCount = rnd.next(1, 25);
    vector<string> words;
    words.reserve(wordCount);

    for (int i = 0; i < wordCount; ++i) {
        int mode = rnd.next(10);
        if (mode < 4) {
            words.push_back(matchingWord());
        } else if (mode < 8) {
            words.push_back(nearMissWord());
        } else if (mode == 8) {
            words.push_back(randomLetters(rnd.next(1, 20)));
        } else {
            words.push_back(rnd.next(2) == 0 ? string(1, 'a') : randomLetters(20));
        }
    }

    shuffle(words.begin(), words.end());
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
