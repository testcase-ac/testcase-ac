#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string makeWord(int from, int to, int salt) {
    string word;
    word.push_back(char('a' + from));

    int middleLen = rnd.next(0, 4);
    for (int i = 0; i < middleLen; ++i) {
        int x = (salt + i * 7 + rnd.next(0, 25)) % 26;
        word.push_back(char('a' + x));
    }

    if (word.size() == 1 || from != to || rnd.next(0, 1)) {
        word.push_back(char('a' + to));
    }

    return word;
}

void addWord(vector<string>& words, set<string>& used, int from, int to) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        string word = makeWord(from, to, int(words.size()) + attempt);
        if (used.insert(word).second) {
            words.push_back(word);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> words;
    set<string> used;

    int mode = rnd.next(0, 4);
    int letters = rnd.next(2, 10);

    if (mode == 0) {
        int n = rnd.next(1, 18);
        for (int i = 0; i < n; ++i) {
            addWord(words, used, i % letters, (i + 1) % letters);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        for (int i = 0; i + 1 < n; ++i) {
            addWord(words, used, i % letters, (i + 1) % letters);
        }
        addWord(words, used, (n + 3) % 26, (n + 3) % 26);
    } else if (mode == 2) {
        int center = rnd.next(0, letters - 1);
        int spokes = rnd.next(2, letters);
        for (int i = 0; i < spokes; ++i) {
            int v = (center + i + 1) % letters;
            addWord(words, used, center, v);
            if (rnd.next(0, 1)) addWord(words, used, v, center);
        }
    } else if (mode == 3) {
        int target = rnd.next(0, letters - 1);
        for (int i = 0; i < letters; ++i) {
            if (i != target) addWord(words, used, i, target);
        }
        int extras = rnd.next(0, 8);
        for (int i = 0; i < extras; ++i) {
            addWord(words, used, rnd.next(0, letters - 1), rnd.next(0, letters - 1));
        }
    } else {
        int m = rnd.next(1, 60);
        for (int i = 0; i < m; ++i) {
            int from = rnd.next(0, letters - 1);
            int to = rnd.next(0, letters - 1);
            addWord(words, used, from, to);
        }
    }

    if (rnd.next(0, 3) == 0) {
        int isolated = rnd.next(letters, 25);
        addWord(words, used, isolated, isolated);
    }

    shuffle(words.begin(), words.end());

    println(int(words.size()));
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
