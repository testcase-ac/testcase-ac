#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const string target = "UNIST";
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string randomWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string prefixedWord(const string& prefix) {
    string s = prefix;
    int extra = rnd.next(0, 25 - (int)s.size());
    for (int i = 0; i < extra; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

void addNoise(vector<string>& words, int count) {
    for (int i = 0; i < count; ++i) {
        if (rnd.next(4) == 0) {
            words.push_back(randomWord(20, 25));
        } else {
            words.push_back(randomWord(1, 8));
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> words;
    int mode = rnd.next(5);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int start = rnd.next(5);
            int len = rnd.next(1, 5 - start);
            if (rnd.next(3) == 0) {
                words.push_back(randomWord(1, 25));
            } else {
                words.push_back(prefixedWord(target.substr(start, len)));
            }
        }
    } else if (mode == 1) {
        int pos = 0;
        while (pos < 5) {
            int len = rnd.next(1, 5 - pos);
            words.push_back(prefixedWord(target.substr(pos, len)));
            pos += len;
            addNoise(words, rnd.next(0, 2));
        }
    } else if (mode == 2) {
        addNoise(words, rnd.next(1, 8));
        for (int i = 0; i < 5; ++i) {
            words.push_back(prefixedWord(target.substr(i, 1)));
            addNoise(words, rnd.next(0, 3));
        }
    } else if (mode == 3) {
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(2) == 0) {
                int len = rnd.next(1, 5);
                words.push_back(prefixedWord(target.substr(0, len)));
            } else {
                words.push_back(randomWord(1, 25));
            }
        }
    } else {
        int n = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            words.push_back(randomWord(1, 25));
        }
    }

    shuffle(words.begin(), words.end());

    println((int)words.size());
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
