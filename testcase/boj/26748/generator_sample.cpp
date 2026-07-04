#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomDistinctLetters(int count) {
    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());
    return letters.substr(0, count);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 80);
    string s;

    if (mode == 0) {
        char c = rnd.next('a', 'z');
        s.assign(n, c);
    } else if (mode == 1) {
        string letters = randomDistinctLetters(rnd.next(2, 4));
        for (int i = 0; i < n; ++i) {
            s += letters[i % (int)letters.size()];
        }
    } else if (mode == 2) {
        string letters = randomDistinctLetters(rnd.next(3, 6));
        s += rnd.any(letters);
        while ((int)s.size() < n) {
            char c = rnd.any(letters);
            if (c == s.back()) continue;
            if ((int)s.size() >= 2 && c == s[(int)s.size() - 2]) continue;
            s += c;
        }
    } else if (mode == 3) {
        string letters = randomDistinctLetters(rnd.next(3, 8));
        while ((int)s.size() < n) {
            if (!s.empty() && rnd.next(0, 3) == 0) {
                s += s.back();
            } else if ((int)s.size() >= 2 && rnd.next(0, 3) == 0) {
                s += s[(int)s.size() - 2];
            } else {
                s += rnd.any(letters);
            }
        }
    } else if (mode == 4) {
        vector<string> blocks = {"aa", "aba", "abba", "abcba", "abca", "abc"};
        while ((int)s.size() < n) {
            string block = rnd.any(blocks);
            char offset = rnd.next(0, 20);
            for (char ch : block) {
                if ((int)s.size() == n) break;
                s += char('a' + (ch - 'a' + offset) % 26);
            }
        }
    } else if (mode == 5) {
        string letters = randomDistinctLetters(rnd.next(2, 10));
        for (int i = 0; i < n; ++i) {
            s += rnd.any(letters);
        }
    } else {
        n = rnd.next(70, 180);
        string letters = randomDistinctLetters(rnd.next(2, 26));
        for (int i = 0; i < n; ++i) {
            s += rnd.any(letters);
        }
    }

    println(s);
    return 0;
}
