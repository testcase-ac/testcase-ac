#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomWord(int minLen, int maxLen, const string& alphabet) {
    int len = rnd.next(minLen, maxLen);
    string word;
    for (int i = 0; i < len; ++i) {
        word += rnd.any(alphabet);
    }
    return word;
}

void addPrefixChain(vector<string>& words, const string& base, int maxLen) {
    int from = rnd.next(1, min<int>(3, maxLen));
    for (int len = from; len <= (int)base.size(); ++len) {
        words.push_back(base.substr(0, len));
        if ((int)words.size() >= maxLen) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> words;
    int mode = rnd.next(0, 3);
    string alphabet = "abcdef";

    if (mode == 0) {
        int groups = rnd.next(2, 6);
        for (int g = 0; g < groups; ++g) {
            string base = randomWord(4, 12, alphabet);
            addPrefixChain(words, base, 50);
        }
    } else if (mode == 1) {
        int uniqueCount = rnd.next(2, 10);
        vector<string> pool;
        for (int i = 0; i < uniqueCount; ++i) {
            pool.push_back(randomWord(1, 10, alphabet));
        }
        int n = rnd.next(uniqueCount, 50);
        for (int i = 0; i < n; ++i) {
            words.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        int trunks = rnd.next(2, 5);
        for (int t = 0; t < trunks; ++t) {
            string prefix = randomWord(1, 4, alphabet);
            words.push_back(prefix);
            int branches = rnd.next(2, 8);
            for (int b = 0; b < branches; ++b) {
                words.push_back(prefix + randomWord(1, 8, alphabet));
                if ((int)words.size() >= 50) break;
            }
            if ((int)words.size() >= 50) break;
        }
    } else {
        int n = rnd.next(5, 30);
        string wideAlphabet = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < n; ++i) {
            string word;
            word += wideAlphabet[i % (int)wideAlphabet.size()];
            word += randomWord(2, 12, wideAlphabet);
            words.push_back(word);
        }
    }

    shuffle(words.begin(), words.end());
    int n = rnd.next(1, min<int>(50, words.size()));
    words.resize(n);

    println(n);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
