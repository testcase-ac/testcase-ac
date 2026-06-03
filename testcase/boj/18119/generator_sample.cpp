#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string vowels = "aeiou";
    const string consonants = "bcdfghjklmnpqrstvwxyz";

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 40);
    int alphabetSize = rnd.next(1, 10);
    int maxWordLen = rnd.next(1, 20);

    string active = consonants.substr(0, alphabetSize);
    shuffle(active.begin(), active.end());

    vector<string> words;
    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 4);
        int len = rnd.next(1, maxWordLen);
        string word;

        if (mode == 0) {
            char c = rnd.any(active);
            int repeat = rnd.next(1, len);
            word.assign(repeat, c);
            while ((int)word.size() < len) word += rnd.any(vowels);
        } else if (mode == 1) {
            int need = rnd.next(1, min(4, (int)active.size()));
            string pool = active;
            shuffle(pool.begin(), pool.end());
            pool.resize(need);
            for (int j = 0; j < len; ++j) {
                word += rnd.next(0, 3) == 0 ? rnd.any(vowels) : rnd.any(pool);
            }
        } else if (mode == 2) {
            for (int j = 0; j < len; ++j) word += rnd.any(vowels);
        } else {
            for (int j = 0; j < len; ++j) {
                word += rnd.next(0, 1) == 0 ? rnd.any(active) : rnd.any(vowels);
            }
        }

        shuffle(word.begin(), word.end());
        words.push_back(word);
    }

    vector<bool> remembered(26, true);
    vector<pair<int, char>> queries;
    for (int i = 0; i < m; ++i) {
        vector<char> forgotten;
        vector<char> known;
        for (char c : active) {
            if (remembered[c - 'a']) {
                known.push_back(c);
            } else {
                forgotten.push_back(c);
            }
        }

        bool shouldForget = forgotten.empty() || (!known.empty() && rnd.next(0, 99) < 55);
        if (shouldForget) {
            char c = rnd.any(known);
            remembered[c - 'a'] = false;
            queries.push_back({1, c});
        } else {
            char c = rnd.any(forgotten);
            remembered[c - 'a'] = true;
            queries.push_back({2, c});
        }
    }

    println(n, m);
    for (const string& word : words) println(word);
    for (const auto& query : queries) println(query.first, query.second);

    return 0;
}
