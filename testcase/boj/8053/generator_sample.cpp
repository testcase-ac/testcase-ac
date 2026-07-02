#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) {
        word.push_back(rnd.any(alphabet));
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 5);
    int mode = rnd.next(0, 4);
    int alphabetSize = rnd.next(1, 8);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    alphabet.resize(alphabetSize);

    vector<string> words;
    words.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            words.push_back(randomWord(rnd.next(1, 12), alphabet));
        }
    } else if (mode == 1) {
        string common = randomWord(rnd.next(1, 6), alphabet);
        for (int i = 0; i < n; ++i) {
            string left = randomWord(rnd.next(0, 8), alphabet);
            string right = randomWord(rnd.next(0, 8), alphabet);
            words.push_back(left + common + right);
        }
    } else if (mode == 2) {
        char c = rnd.any(alphabet);
        for (int i = 0; i < n; ++i) {
            words.push_back(string(rnd.next(1, 20), c));
        }
    } else if (mode == 3) {
        string pattern = randomWord(rnd.next(1, 4), alphabet);
        for (int i = 0; i < n; ++i) {
            int repeats = rnd.next(1, 8);
            string word;
            for (int j = 0; j < repeats; ++j) {
                word += pattern;
            }
            if (rnd.next(0, 1)) {
                word += randomWord(rnd.next(0, 4), alphabet);
            }
            words.push_back(word);
        }
    } else {
        string common = randomWord(rnd.next(1, 5), alphabet);
        for (int i = 0; i < n; ++i) {
            string word = randomWord(rnd.next(1, 10), alphabet);
            int pos = rnd.next(0, static_cast<int>(word.size()));
            word.insert(pos, common);
            if (rnd.next(0, 1)) {
                reverse(word.begin(), word.end());
            }
            words.push_back(word);
        }
    }

    println(n);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
