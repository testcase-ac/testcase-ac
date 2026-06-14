#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomWord(int len, char lo = 'a', char hi = 'z') {
    string s;
    for (int i = 0; i < len; ++i) s += char(rnd.next((int)lo, (int)hi));
    return s;
}

string repeatString(const string& s, int count) {
    string result;
    for (int i = 0; i < count; ++i) result += s;
    return result;
}

void trimToLimit(string& s) {
    if ((int)s.size() > 200) s.resize(200);
    if (s.empty()) s = "a";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    string s;

    if (mode == 0) {
        s = string(rnd.next(1, 200), char(rnd.next((int)'a', (int)'z')));
    } else if (mode == 1) {
        int alphabet = rnd.next(1, 6);
        s = randomWord(rnd.next(2, 80), 'a', char('a' + alphabet - 1));
    } else if (mode == 2) {
        string block = randomWord(rnd.next(1, 12), 'a', 'f');
        s = repeatString(block, rnd.next(2, max(2, 200 / (int)block.size())));
    } else if (mode == 3) {
        string inner = repeatString(randomWord(rnd.next(1, 5), 'a', 'h'), rnd.next(2, 8));
        string block = randomWord(rnd.next(0, 6), 'i', 'p') + inner + randomWord(rnd.next(0, 6), 'q', 'z');
        s = repeatString(block, rnd.next(2, max(2, 200 / (int)block.size())));
    } else if (mode == 4) {
        string block = randomWord(rnd.next(2, 15), 'a', 'j');
        s = repeatString(block, rnd.next(2, max(2, 200 / (int)block.size())));
        s[rnd.next((int)s.size())] = char(rnd.next((int)'k', (int)'z'));
    } else if (mode == 5) {
        int blockLen = rnd.next(1, 9);
        vector<string> blocks;
        for (int i = 0; i < rnd.next(2, 5); ++i) {
            string block = randomWord(blockLen, char('a' + i * 3), char('c' + i * 3));
            blocks.push_back(repeatString(block, rnd.next(2, 8)));
        }
        shuffle(blocks.begin(), blocks.end());
        for (const string& block : blocks) s += block;
    } else if (mode == 6) {
        string left = randomWord(rnd.next(1, 20), 'a', 'm');
        string middle = repeatString(randomWord(rnd.next(1, 8), 'n', 't'), rnd.next(2, 12));
        string right = randomWord(rnd.next(1, 20), 'u', 'z');
        s = left + middle + right;
    } else {
        string base = randomWord(rnd.next(1, 7), 'a', 'd');
        string doubled = repeatString(base, rnd.next(2, 10));
        s = randomWord(rnd.next(0, 8), 'e', 'h') + repeatString(doubled, rnd.next(2, 8));
    }

    trimToLimit(s);
    println(s);
    return 0;
}
