#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

static string randomWord(int len, int alphabetSize) {
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) {
        word.push_back(static_cast<char>('a' + rnd.next(alphabetSize)));
    }
    return word;
}

static string shuffledWord(string word) {
    shuffle(word.begin(), word.end());
    return word;
}

static string uniqueWord(set<string>& used, int len, int alphabetSize) {
    for (int tries = 0; tries < 1000; ++tries) {
        string word = randomWord(len, alphabetSize);
        if (used.insert(word).second) {
            return word;
        }
    }

    for (char a = 'a'; a <= 'z'; ++a) {
        string word(len, a);
        if (used.insert(word).second) {
            return word;
        }
    }

    quitf(_fail, "could not create a unique vocabulary word");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int v = rnd.next(5, 10);
        int s = rnd.next(1, 5);
        int alphabetSize = rnd.next(2, 8);

        set<string> used;
        vector<string> vocabulary;
        vector<vector<int>> byLength(6);

        while (static_cast<int>(vocabulary.size()) < v) {
            int mode = rnd.next(3);
            int len = rnd.next(1, 5);
            string word;

            if (mode == 0 && !vocabulary.empty()) {
                vector<int> candidates;
                for (int i = 0; i < static_cast<int>(vocabulary.size()); ++i) {
                    if (static_cast<int>(vocabulary[i].size()) == len) {
                        candidates.push_back(i);
                    }
                }
                if (!candidates.empty()) {
                    word = shuffledWord(vocabulary[rnd.any(candidates)]);
                }
            }

            if (word.empty() || used.count(word)) {
                word = uniqueWord(used, len, alphabetSize);
            } else {
                used.insert(word);
            }

            byLength[word.size()].push_back(static_cast<int>(vocabulary.size()));
            vocabulary.push_back(word);
        }

        println(v, s);
        for (const string& word : vocabulary) {
            println(word);
        }

        for (int i = 0; i < s; ++i) {
            int targetLength = rnd.next(1, 50);
            string cipher;

            while (cipher.empty() || static_cast<int>(cipher.size()) < targetLength) {
                vector<int> usableLengths;
                for (int len = 1; len <= 5; ++len) {
                    if (!byLength[len].empty() &&
                        static_cast<int>(cipher.size()) + len <= 50) {
                        usableLengths.push_back(len);
                    }
                }
                if (usableLengths.empty()) {
                    break;
                }

                int len = rnd.any(usableLengths);
                int index = rnd.any(byLength[len]);
                cipher += shuffledWord(vocabulary[index]);

                if (!cipher.empty() && rnd.next(3) == 0) {
                    break;
                }
            }

            println(cipher);
        }
    }

    return 0;
}
