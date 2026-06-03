#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(rnd.any(alphabet));
    }
    return result;
}

string repeated(char c, int length) {
    return string(length, c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> alphabets = {"AB", "ABC", "ABCD", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int testCases = rnd.next(6, 14);
    println(testCases);

    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(0, 5);
        string word;
        string text;

        if (mode == 0) {
            int length = rnd.next(1, 24);
            word = randomString(length, rnd.any(alphabets));
            text = word;
        } else if (mode == 1) {
            int wordLength = rnd.next(1, 8);
            int textLength = rnd.next(wordLength, 40);
            char c = rnd.any(string("ABC"));
            word = repeated(c, wordLength);
            text = repeated(c, textLength);
        } else if (mode == 2) {
            int period = rnd.next(2, 5);
            string base = randomString(period, "ABC");
            int repeats = rnd.next(2, 6);
            word.clear();
            for (int i = 0; i < repeats; ++i) word += base;
            int extraRepeats = rnd.next(0, 5);
            text = word;
            for (int i = 0; i < extraRepeats; ++i) text += base;
        } else if (mode == 3) {
            int wordLength = rnd.next(2, 18);
            int textLength = rnd.next(wordLength, 45);
            word = randomString(wordLength, "ABC");
            text = randomString(textLength, "XYZ");
        } else if (mode == 4) {
            int wordLength = rnd.next(1, 12);
            int prefixLength = rnd.next(0, 15);
            int suffixLength = rnd.next(0, 15);
            word = randomString(wordLength, rnd.any(alphabets));
            text = randomString(prefixLength, "XYZ") + word + randomString(suffixLength, "XYZ");
        } else {
            int wordLength = rnd.next(3, 20);
            int textLength = rnd.next(wordLength, 60);
            string alphabet = rnd.any(alphabets);
            word = randomString(wordLength, alphabet);
            text = randomString(textLength, alphabet);
            if (rnd.next(0, 1) == 1) {
                int pos = rnd.next(0, textLength - wordLength);
                copy(word.begin(), word.end(), text.begin() + pos);
            }
        }

        println(word);
        println(text);
    }

    return 0;
}
