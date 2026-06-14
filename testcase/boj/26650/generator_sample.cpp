#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeGramPan() {
    string s;
    for (char c = 'A'; c <= 'Z'; ++c) {
        int repeats = rnd.next(1, 3);
        s.append(repeats, c);
    }
    return s;
}

string makeAlmostGramPan() {
    string s = makeGramPan();
    int mode = rnd.next(4);

    if (mode == 0) {
        char missing = char('A' + rnd.next(26));
        s.erase(remove(s.begin(), s.end(), missing), s.end());
    } else if (mode == 1) {
        int pos = rnd.next((int)s.size());
        s[pos] = char('A' + rnd.next(26));
    } else if (mode == 2) {
        int pos = rnd.next(1, (int)s.size() - 1);
        swap(s[pos - 1], s[pos]);
    } else {
        int pos = rnd.next((int)s.size());
        s.insert(pos, 1, char('A' + rnd.next(26)));
    }

    if (s.empty()) s = "A";
    return s;
}

string makeNoise(int length) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int maxLetter = rnd.next(0, 25);
    if (rnd.next(100) < 35) maxLetter = rnd.next(0, 5);

    string s;
    for (int i = 0; i < length; ++i) {
        if (rnd.next(100) < 15) {
            s += rnd.any(alphabet);
        } else {
            s += char('A' + rnd.next(0, maxLetter));
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string s;

    if (mode == 0) {
        s = makeGramPan();
    } else if (mode == 1) {
        int copies = rnd.next(2, 4);
        for (int i = 0; i < copies; ++i) {
            if (!s.empty() && rnd.next(2)) s += rnd.any(string("AZM"));
            s += makeGramPan();
        }
    } else if (mode == 2) {
        s = makeAlmostGramPan();
    } else if (mode == 3) {
        s = makeNoise(rnd.next(1, 80));
    } else if (mode == 4) {
        s = makeNoise(rnd.next(1, 25)) + makeGramPan() + makeNoise(rnd.next(1, 25));
    } else {
        vector<string> blocks;
        int blockCount = rnd.next(2, 7);
        for (int i = 0; i < blockCount; ++i) {
            int blockMode = rnd.next(3);
            if (blockMode == 0) blocks.push_back(makeGramPan());
            if (blockMode == 1) blocks.push_back(makeAlmostGramPan());
            if (blockMode == 2) blocks.push_back(makeNoise(rnd.next(1, 20)));
        }
        shuffle(blocks.begin(), blocks.end());
        for (string block : blocks) s += block;
    }

    println(s);
    return 0;
}
