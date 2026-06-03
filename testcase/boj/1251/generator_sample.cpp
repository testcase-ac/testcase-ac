#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomWord(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int len;
    string word;

    if (mode == 0) {
        len = rnd.next(3, 6);
        word = randomWord(len, "abc");
    } else if (mode == 1) {
        len = rnd.next(45, 50);
        word = randomWord(len, "abcdefghijklmnopqrstuvwxyz");
    } else if (mode == 2) {
        len = rnd.next(3, 50);
        char c = char('a' + rnd.next(0, 25));
        word.assign(len, c);
    } else if (mode == 3) {
        len = rnd.next(3, 30);
        int start = rnd.next(0, 25);
        int step = rnd.next(1, 5);
        for (int i = 0; i < len; ++i) {
            word += char('a' + (start + i * step) % 26);
        }
    } else if (mode == 4) {
        len = rnd.next(3, 30);
        int start = rnd.next(0, 25);
        int step = rnd.next(1, 5);
        for (int i = 0; i < len; ++i) {
            word += char('a' + (start - i * step % 26 + 26) % 26);
        }
    } else if (mode == 5) {
        int a = rnd.next(1, 16);
        int b = rnd.next(1, 16);
        int c = rnd.next(1, 16);
        vector<char> letters = {
            char('a' + rnd.next(0, 25)),
            char('a' + rnd.next(0, 25)),
            char('a' + rnd.next(0, 25)),
        };
        word.append(a, letters[0]);
        word.append(b, letters[1]);
        word.append(c, letters[2]);
    } else {
        len = rnd.next(3, 30);
        word = randomWord(len, "abcxyz");
        if (rnd.next(0, 1)) {
            reverse(word.begin(), word.end());
        }
    }

    println(word);
    return 0;
}
