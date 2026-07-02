#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomWord(int minLen, int maxLen, const string& alphabet) {
    int len = rnd.next(minLen, maxLen);
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) {
        word.push_back(rnd.any(alphabet));
    }
    return word;
}

string freshWord(set<string>& used, int minLen, int maxLen, const string& alphabet) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        string word = randomWord(minLen, maxLen, alphabet);
        if (!used.count(word)) return word;
    }

    for (int len = minLen; len <= maxLen; ++len) {
        int total = 1;
        for (int i = 0; i < len; ++i) total *= static_cast<int>(alphabet.size());

        for (int mask = 0; mask < total; ++mask) {
            int value = mask;
            string word(len, alphabet[0]);
            for (int i = 0; i < len; ++i) {
                word[i] = alphabet[value % static_cast<int>(alphabet.size())];
                value /= static_cast<int>(alphabet.size());
            }
            if (!used.count(word)) return word;
        }
    }

    quitf(_fail, "could not create a unique word");
}

void addWord(vector<string>& words, set<string>& used, const string& word) {
    if (used.insert(word).second) words.push_back(word);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = rnd.next(0, 2) == 0 ? "abc" : "abcd";
    vector<string> words;
    set<string> used;

    int mode = rnd.next(0, 4);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            addWord(words, used, freshWord(used, 1, 3, alphabet));
        }
        while (static_cast<int>(words.size()) < n) {
            addWord(words, used, freshWord(used, 1, 3, alphabet));
        }

        string a = rnd.any(words);
        string b = rnd.any(words);
        string c = rnd.any(words);
        s = a + b + c;
    } else if (mode == 1) {
        addWord(words, used, "a");
        addWord(words, used, "aa");
        addWord(words, used, "aaa");
        addWord(words, used, "b");
        addWord(words, used, "ab");
        addWord(words, used, "ba");

        int extra = rnd.next(0, 4);
        for (int i = 0; i < extra; ++i) {
            addWord(words, used, freshWord(used, 1, 4, "ab"));
        }
        s = string(rnd.next(3, 10), rnd.next(0, 1) == 0 ? 'a' : 'b');
    } else if (mode == 2) {
        string left = freshWord(used, 1, 3, alphabet);
        addWord(words, used, left);
        string middle = left + rnd.any(alphabet);
        addWord(words, used, middle);
        addWord(words, used, string(1, rnd.any(alphabet)) + left);
        addWord(words, used, freshWord(used, 1, 4, alphabet));
        addWord(words, used, freshWord(used, 2, 5, alphabet));

        shuffle(words.begin(), words.end());
        s = words[0] + words[1] + words[2];
    } else if (mode == 3) {
        int n = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            addWord(words, used, freshWord(used, 1, 5, alphabet));
        }

        s = randomWord(3, 18, alphabet);
    } else {
        addWord(words, used, "a");
        addWord(words, used, "b");
        addWord(words, used, "c");
        addWord(words, used, "aa");
        addWord(words, used, "ab");
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) {
            addWord(words, used, freshWord(used, 1, 4, alphabet));
        }

        string a = rnd.any(words);
        string b = rnd.any(words);
        string c = rnd.any(words);
        s = a + b + c;
    }

    shuffle(words.begin(), words.end());

    println(static_cast<int>(words.size()));
    for (const string& word : words) {
        println(word);
    }
    println(s);

    return 0;
}
