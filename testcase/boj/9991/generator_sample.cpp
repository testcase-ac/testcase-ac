#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomWord(int minLen, int maxLen, const string& alphabet) {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += alphabet[rnd.next(static_cast<int>(alphabet.size()))];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> stems = {"a", "b", "c", "d", "aa", "ab", "ba", "z"};
    string alphabet = "abc";
    if (rnd.next(4) == 0) alphabet = "abcd";
    if (rnd.next(5) == 0) alphabet = "xyz";

    int w = rnd.next(6, 28);
    int n = rnd.next(8, 36);

    set<string> used;
    vector<string> words;
    for (const string& stem : stems) {
        if (static_cast<int>(words.size()) >= w) break;
        if (used.insert(stem).second) words.push_back(stem);
    }

    while (static_cast<int>(words.size()) < w) {
        string word;
        if (rnd.next(100) < 70) {
            string stem = rnd.any(stems);
            word = stem + randomWord(0, 5, alphabet);
        } else {
            word = randomWord(1, 8, alphabet);
        }
        if (used.insert(word).second) words.push_back(word);
    }

    shuffle(words.begin(), words.end());

    vector<pair<int, string>> queries;
    vector<string> sortedWords = words;
    sort(sortedWords.begin(), sortedWords.end());

    while (static_cast<int>(queries.size()) < n) {
        string prefix;
        int mode = rnd.next(100);
        if (mode < 55) {
            const string& base = rnd.any(words);
            int len = rnd.next(1, static_cast<int>(base.size()));
            prefix = base.substr(0, len);
        } else if (mode < 80) {
            prefix = rnd.any(stems);
        } else if (mode < 92) {
            prefix = string(1, static_cast<char>('a' + rnd.next(26)));
        } else {
            prefix = randomWord(1, 6, "abcdefghijklmnopqrstuvwxyz");
        }

        int completions = 0;
        for (const string& word : sortedWords) {
            if (word.size() >= prefix.size() && word.compare(0, prefix.size(), prefix) == 0) {
                ++completions;
            }
        }

        int k;
        if (completions == 0) {
            k = rnd.next(1, 5);
        } else if (rnd.next(100) < 75) {
            k = rnd.next(1, completions);
        } else {
            k = completions + rnd.next(1, 8);
        }
        if (rnd.next(20) == 0) k = rnd.next(1000000, 1000000000);
        queries.push_back({k, prefix});
    }

    println(w, n);
    for (const string& word : words) println(word);
    for (const auto& query : queries) println(query.first, query.second);

    return 0;
}
