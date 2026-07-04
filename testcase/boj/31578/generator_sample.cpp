#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int minLen, int maxLen, const string& alphabet) {
    int len = rnd.next(minLen, maxLen);
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) word += rnd.any(alphabet);
    return word;
}

string withSharedBlock(const string& block, int maxLen, const string& alphabet) {
    int extra = maxLen - static_cast<int>(block.size());
    int left = rnd.next(0, extra);
    int right = rnd.next(0, extra - left);
    return randomWord(left, left, alphabet) + block + randomWord(right, right, alphabet);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 14);
    int k = rnd.next(1, 20);
    vector<string> words;
    words.reserve(n);

    if (mode == 0) {
        k = rnd.next(1, 4);
        string block = randomWord(k, k, alphabet);
        for (int i = 0; i < n; ++i) {
            words.push_back(withSharedBlock(block, 20, alphabet));
        }
    } else if (mode == 1) {
        k = rnd.next(2, 8);
        string a = randomWord(k, k, alphabet);
        string b = randomWord(k, k, alphabet);
        for (int i = 0; i < n; ++i) {
            words.push_back(withSharedBlock(i % 2 == 0 ? a : b, 20, alphabet));
        }
    } else if (mode == 2) {
        k = rnd.next(1, 20);
        string base = randomWord(1, 20, alphabet);
        for (int i = 0; i < n; ++i) {
            words.push_back(rnd.next(0, 3) == 0 ? base : randomWord(1, 20, alphabet));
        }
    } else if (mode == 3) {
        k = rnd.next(1, 20);
        int len = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            words.push_back(randomWord(len, len, alphabet.substr(0, rnd.next(1, 6))));
        }
    } else if (mode == 4) {
        k = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            words.push_back(randomWord(1, min(20, k), alphabet));
        }
    } else {
        k = rnd.next(1, 12);
        string chain = randomWord(min(20, k + n), min(20, k + n), alphabet);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, min(20, static_cast<int>(chain.size())));
            int start = rnd.next(0, static_cast<int>(chain.size()) - len);
            words.push_back(chain.substr(start, len));
        }
    }

    shuffle(words.begin(), words.end());

    println(n, k);
    for (const string& word : words) println(word);
    return 0;
}
