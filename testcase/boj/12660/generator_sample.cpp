#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const string TARGET = "welcome to code jam";
const string LETTERS = "abcdefghijklmnopqrstuvwxyz";

string repeatedChars() {
    string s;
    for (char c : TARGET) {
        int copies = rnd.next(1, 3);
        s.append(copies, c);
    }
    return s;
}

string randomNoise(int len, bool allowTargetLetters) {
    string alphabet = allowTargetLetters ? LETTERS : string("abdfghiknpqrsuvwxyz");
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        if (i > 0 && rnd.next(5) == 0 && s.back() != ' ') {
            s.push_back(' ');
        } else {
            s.push_back(rnd.any(alphabet));
        }
    }
    if (s.front() == ' ') s.front() = rnd.any(alphabet);
    if (s.back() == ' ') s.back() = rnd.any(alphabet);
    return s;
}

string interleavedTarget() {
    string s;
    for (char c : TARGET) {
        if (!s.empty() && rnd.next(4) == 0 && s.back() != ' ') s.push_back(' ');
        s.push_back(c);
        int noiseLen = rnd.next(0, 2);
        for (int i = 0; i < noiseLen; ++i) s.push_back(rnd.any(LETTERS));
    }
    if (s.back() == ' ') s.push_back(rnd.any(LETTERS));
    return s;
}

string fragmentShuffle() {
    vector<string> parts = {"welcome", "to", "code", "jam"};
    shuffle(parts.begin(), parts.end());
    string s = parts[0];
    for (int i = 1; i < int(parts.size()); ++i) {
        s += rnd.next(1, 3) == 1 ? " " : string(1, rnd.any(LETTERS));
        s += parts[i];
    }
    return s;
}

string nearMiss() {
    string s = TARGET;
    int pos = rnd.next(int(s.size()));
    if (s[pos] == ' ') {
        s[pos] = rnd.any(LETTERS);
    } else {
        char replacement = rnd.any(LETTERS);
        while (replacement == s[pos]) replacement = rnd.any(LETTERS);
        s[pos] = replacement;
    }
    if (rnd.next(2) == 0) s += " " + randomNoise(rnd.next(1, 8), true);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = rnd.next(6);
        string s;
        if (mode == 0) {
            s = randomNoise(rnd.next(1, 28), false);
        } else if (mode == 1) {
            s = TARGET;
        } else if (mode == 2) {
            s = repeatedChars();
        } else if (mode == 3) {
            s = interleavedTarget();
        } else if (mode == 4) {
            s = fragmentShuffle();
        } else {
            s = nearMiss();
        }

        if (int(s.size()) > 80) s.resize(80);
        if (s.front() == ' ') s.front() = 'a';
        if (s.back() == ' ') s.back() = 'z';
        println(s);
    }

    return 0;
}
