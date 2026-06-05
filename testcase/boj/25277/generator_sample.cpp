#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string word;
    for (int i = 0; i < len; ++i) {
        word += char('a' + rnd.next(26));
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> forbidden = {"he", "him", "she", "her"};
    const vector<string> nearMisses = {
        "h", "hi", "hem", "hers", "hero", "sher", "shim", "they", "them",
        "sheared", "sheep", "herd", "helped", "abcdefghijklmnopqrst"};

    int mode = rnd.next(5);
    int n = 1;
    vector<string> words;

    if (mode == 0) {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            words.push_back(rnd.any(forbidden));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            words.push_back(rnd.any(nearMisses));
        }
    } else if (mode == 2) {
        n = rnd.next(8, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 35) {
                words.push_back(rnd.any(forbidden));
            } else if (rnd.next(100) < 70) {
                words.push_back(rnd.any(nearMisses));
            } else {
                words.push_back(randomWord(1, 20));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 24);
        for (int i = 0; i < n; ++i) {
            int len = (i % 2 == 0 ? 20 : rnd.next(1, 20));
            words.push_back(randomWord(len, len));
        }
    } else {
        n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(100);
            if (pick < 20) {
                words.push_back(rnd.any(forbidden));
            } else if (pick < 55) {
                words.push_back(rnd.any(nearMisses));
            } else {
                words.push_back(randomWord(1, 8));
            }
        }
        shuffle(words.begin(), words.end());
    }

    println(n);
    println(words);

    return 0;
}
