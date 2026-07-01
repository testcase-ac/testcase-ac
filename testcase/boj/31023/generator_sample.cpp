#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

namespace {

string randomWord(int minLen = 1, int maxLen = 8) {
    int len = rnd.next(minLen, maxLen);
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) {
        word.push_back(char('a' + rnd.next(26)));
    }
    return word;
}

string randomCase(string word) {
    for (char& c : word) {
        if (rnd.next(2) == 0) {
            c = char(toupper(static_cast<unsigned char>(c)));
        }
    }
    return word;
}

string separator() {
    const vector<string> separators = {
        " ", "  ", ", ", "...", "??? ", "!!! ", "-", "123", " / "
    };
    return rnd.any(separators);
}

vector<string> makePleasantWords(int p) {
    vector<string> words;
    while (int(words.size()) < p) {
        string word = randomWord();
        if (find(words.begin(), words.end(), word) == words.end()) {
            words.push_back(word);
        }
    }
    return words;
}

string makeSongLine(const vector<string>& words) {
    string line;
    if (rnd.next(3) == 0) {
        line += rnd.any(vector<string>{"...", "123", "!!!", " "});
    }

    for (int i = 0; i < int(words.size()); ++i) {
        if (i > 0) {
            line += separator();
        }
        line += randomCase(words[i]);
    }

    if (rnd.next(3) == 0) {
        line += rnd.any(vector<string>{"!", ".", "???", " 42"});
    }

    if (line.empty()) {
        line = "a";
    }
    if (int(line.size()) > 100) {
        line.resize(100);
        while (!line.empty() && isalpha(static_cast<unsigned char>(line.back()))) {
            line.pop_back();
        }
        if (line.empty()) {
            line = words[0].substr(0, min<int>(100, words[0].size()));
        }
    }
    return line;
}

string randomNonPleasantWord(const vector<string>& pleasant) {
    while (true) {
        string word = randomWord();
        if (find(pleasant.begin(), pleasant.end(), word) == pleasant.end()) {
            return word;
        }
    }
}

vector<string> makeSongWords(const vector<string>& pleasant, int totalWords, int pleasantWords) {
    vector<string> words;
    for (int i = 0; i < pleasantWords; ++i) {
        words.push_back(rnd.any(pleasant));
    }
    for (int i = pleasantWords; i < totalWords; ++i) {
        words.push_back(randomNonPleasantWord(pleasant));
    }
    shuffle(words.begin(), words.end());
    return words;
}

void emitCase() {
    int p = rnd.next(1, 8);
    vector<string> pleasant = makePleasantWords(p);

    println(p);
    for (const string& word : pleasant) {
        println(word);
    }

    int totalWords = rnd.next(1, 18);
    int mode = rnd.next(4);
    int pleasantWords = 0;
    if (mode == 0) {
        pleasantWords = (3 * totalWords + 3) / 4;
    } else if (mode == 1) {
        pleasantWords = max(0, (3 * totalWords - 1) / 4);
    } else if (mode == 2) {
        pleasantWords = rnd.next(0, totalWords);
    } else {
        pleasantWords = totalWords;
    }

    vector<string> songWords = makeSongWords(pleasant, totalWords, pleasantWords);
    int l = rnd.next(1, min(5, totalWords));
    vector<vector<string>> lines(l);
    for (int i = 0; i < totalWords; ++i) {
        lines[i % l].push_back(songWords[i]);
    }

    println(l);
    for (const vector<string>& lineWords : lines) {
        println(makeSongLine(lineWords));
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 8);
    println(n);
    for (int tc = 0; tc < n; ++tc) {
        emitCase();
    }

    return 0;
}
