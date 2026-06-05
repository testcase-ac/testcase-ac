#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomWord(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s += rnd.any(alphabet);
    return s;
}

string repeatToLength(const string& base, int len) {
    string s;
    s.reserve(len);
    while ((int)s.size() < len) s += base;
    s.resize(len);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    string s;

    if (mode == 0) {
        int len = rnd.next(2, 30);
        s.assign(len, char('a' + rnd.next(0, 25)));
    } else if (mode == 1) {
        int period = rnd.next(1, 8);
        int repeats = rnd.next(2, 8);
        string alphabet = "abc";
        string base = randomWord(period, alphabet);
        s = repeatToLength(base, period * repeats);
    } else if (mode == 2) {
        int period = rnd.next(2, 10);
        int repeats = rnd.next(2, 5);
        string base = randomWord(period, "abcd");
        s = repeatToLength(base, period * repeats + rnd.next(1, period - 1));
    } else if (mode == 3) {
        int blockLen = rnd.next(2, 8);
        string block = randomWord(blockLen, "abcde");
        int repeats = rnd.next(2, 5);
        s = repeatToLength(block, blockLen * repeats);
        int pos = rnd.next(0, (int)s.size() - 1);
        char replacement = char('a' + rnd.next(0, 25));
        if (replacement == s[pos]) replacement = char('a' + (replacement - 'a' + 1) % 26);
        s[pos] = replacement;
    } else if (mode == 4) {
        int len = rnd.next(2, 30);
        string alphabet = "ab";
        s = randomWord(len, alphabet);
    } else if (mode == 5) {
        vector<string> blocks = {"ab", "aba", "aab", "abc", "abcd"};
        string block = rnd.any(blocks);
        int repeats = rnd.next(2, 6);
        s = repeatToLength(block, (int)block.size() * repeats);
        if (rnd.next(0, 1)) s += block.substr(0, rnd.next(1, (int)block.size()));
    } else {
        int len = rnd.next(2, 30);
        s = randomWord(len, "abcdefghijklmnopqrstuvwxyz");
    }

    println(s);
    return 0;
}
