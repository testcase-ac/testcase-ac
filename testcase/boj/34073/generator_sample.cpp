#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    vector<string> words;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 8);
            words.push_back(rnd.next("[a-z]{" + to_string(len) + "}"));
        }
    } else if (mode == 1) {
        n = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 3);
            words.push_back(rnd.next("[a-z]{" + to_string(len) + "}"));
        }
    } else if (mode == 2) {
        n = rnd.next(1, 6);
        int remainingLetters = rnd.next(n, 100 - (n - 1));
        for (int i = 0; i < n; ++i) {
            int slotsLeft = n - i - 1;
            int len = (i + 1 == n) ? remainingLetters : rnd.next(1, remainingLetters - slotsLeft);
            remainingLetters -= len;
            words.push_back(rnd.next("[a-z]{" + to_string(len) + "}"));
        }
    } else if (mode == 3) {
        n = rnd.next(50, 100);
        for (int i = 0; i < n; ++i) {
            words.push_back(string(1, static_cast<char>('a' + rnd.next(0, 25))));
        }
    } else {
        static const vector<string> pool = {
            "doro", "wan", "voice", "badge", "blue", "archive", "love", "you", "solve", "problem"};
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            string word = rnd.any(pool);
            if (rnd.next(0, 3) == 0) {
                word += static_cast<char>('a' + rnd.next(0, 25));
            }
            words.push_back(word);
        }
    }

    int totalLength = n - 1;
    for (const string& word : words) {
        totalLength += static_cast<int>(word.size());
    }
    while (totalLength > 100) {
        totalLength -= static_cast<int>(words.back().size()) + (words.size() == 1 ? 0 : 1);
        words.pop_back();
    }

    println(static_cast<int>(words.size()));
    for (int i = 0; i < static_cast<int>(words.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << words[i];
    }
    cout << '\n';

    return 0;
}
