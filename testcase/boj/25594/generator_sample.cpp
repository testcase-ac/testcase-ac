#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const vector<string> words = {
    "aespa",   "baekjoon", "cau",   "debug", "edge",  "firefox",
    "golang",  "haegang",  "iu",    "java",  "kotlin", "lol",
    "mips",    "null",     "os",    "python", "query", "roka",
    "solvedac", "tod",     "unix",  "virus", "whale", "xcode",
    "yahoo",   "zebra",
};

string encodedWord(int len, int mode) {
    string s;
    for (int i = 0; i < len; ++i) {
        int idx;
        if (mode == 0) {
            idx = rnd.next(26);
        } else if (mode == 1) {
            idx = rnd.any(vector<int>{0, 2, 8, 14, 19, 20});
        } else {
            idx = rnd.wnext(26, rnd.next(-2, 2));
        }
        s += words[idx];
    }
    return s;
}

void corruptOneCharacter(string& s) {
    int pos = rnd.next(static_cast<int>(s.size()));
    char c = rnd.next('a', 'z');
    if (c == s[pos]) {
        c = static_cast<char>('a' + (c - 'a' + 1) % 26);
    }
    s[pos] = c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int len = rnd.next(1, 24);
    string s;

    if (mode <= 2) {
        s = encodedWord(len, mode);
    } else if (mode == 3) {
        s = encodedWord(len, rnd.next(3));
        corruptOneCharacter(s);
    } else if (mode == 4) {
        int idx = rnd.next(26);
        int prefixLen = rnd.next(1, static_cast<int>(words[idx].size()) - 1);
        s = encodedWord(rnd.next(0, 12), rnd.next(3)) + words[idx].substr(0, prefixLen);
    } else {
        int n = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) {
            s += rnd.next('a', 'z');
        }
    }

    println(s);
    return 0;
}
