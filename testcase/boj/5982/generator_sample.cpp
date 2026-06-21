#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, char lo, char hi) {
    string word;
    for (int i = 0; i < len; ++i) {
        word += char(rnd.next((int)lo, (int)hi));
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int pieces = rnd.next(1, mode == 0 ? 1 : 8);
    int maxWordLen = rnd.next(1, mode == 4 ? 20 : 8);
    char hi = char('a' + rnd.next(0, mode == 5 ? 25 : 5));

    vector<string> chosen;
    string password;
    for (int i = 0; i < pieces; ++i) {
        int len = rnd.next(1, maxWordLen);
        if (mode == 1 && i % 2 == 1) {
            len = 1;
        }
        string word = randomWord(len, 'a', hi);
        chosen.push_back(word);
        password += word;
    }

    set<string> dictSet(chosen.begin(), chosen.end());
    vector<string> dict(dictSet.begin(), dictSet.end());

    int alphabetSize = hi - 'a' + 1;
    int wordSpace = 0;
    int ways = 1;
    for (int len = 1; len <= maxWordLen && wordSpace < 1000; ++len) {
        ways *= alphabetSize;
        wordSpace += ways;
    }

    int targetDictSize = (int)dict.size() + rnd.next(0, 12);
    targetDictSize = min(targetDictSize, wordSpace);
    while ((int)dict.size() < targetDictSize) {
        int len = rnd.next(1, maxWordLen);
        string word = randomWord(len, 'a', hi);
        if (dictSet.insert(word).second) {
            dict.push_back(word);
        }
    }

    if (mode >= 2 && (int)password.size() >= 2) {
        for (int len = 1; len <= 20 && len <= (int)password.size(); ++len) {
            int start = rnd.next(0, (int)password.size() - len);
            string word = password.substr(start, len);
            if (dictSet.insert(word).second) {
                dict.push_back(word);
            }
        }
    }

    shuffle(dict.begin(), dict.end());

    string pattern = password;
    int revealMode = rnd.next(0, 3);
    for (char& c : pattern) {
        int revealPercent = revealMode == 0 ? 0 : (revealMode == 1 ? 20 : 60);
        if (rnd.next(0, 99) >= revealPercent) {
            c = '?';
        }
    }
    if (revealMode != 0 && !pattern.empty()) {
        int pos = rnd.next(0, (int)pattern.size() - 1);
        pattern[pos] = password[pos];
    }

    println((int)password.size(), (int)dict.size());
    println(pattern);
    for (const string& word : dict) {
        println(word);
    }

    return 0;
}
