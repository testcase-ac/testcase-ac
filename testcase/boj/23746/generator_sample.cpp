#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makePattern(int length, int alphabetSize) {
    string pattern;
    pattern.reserve(length);
    for (int i = 0; i < length; ++i) {
        pattern.push_back(static_cast<char>('a' + rnd.next(alphabetSize)));
    }
    return pattern;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(2, 8);
    }

    vector<char> symbols;
    for (int i = 0; i < 26; ++i) symbols.push_back(static_cast<char>('A' + i));
    shuffle(symbols.begin(), symbols.end());
    symbols.resize(n);
    sort(symbols.begin(), symbols.end());

    int alphabetSize = rnd.next(1, mode == 2 ? 4 : 8);
    vector<string> patterns(n);
    for (int i = 0; i < n; ++i) {
        int length = 1;
        if (mode == 0) {
            length = rnd.next(1, 5);
        } else if (mode == 1) {
            length = rnd.next(1, 8);
        } else if (mode == 2) {
            length = rnd.next(1, 3);
        } else if (mode == 3) {
            length = rnd.next(8, 30);
        } else {
            length = rnd.next(1, 20);
        }
        patterns[i] = makePattern(length, alphabetSize);
    }

    int compressedLength = 1;
    if (mode == 0) {
        compressedLength = rnd.next(1, 8);
    } else if (mode == 2) {
        compressedLength = rnd.next(15, 35);
    } else {
        compressedLength = rnd.next(2, 15);
    }

    string compressed;
    vector<int> prefix(1, 0);
    for (int i = 0; i < compressedLength; ++i) {
        int index = 0;
        if (mode == 4 && i % 3 == 0) {
            index = rnd.next(min(n, 2));
        } else {
            index = rnd.next(n);
        }
        compressed.push_back(symbols[index]);
        prefix.push_back(prefix.back() + static_cast<int>(patterns[index].size()));
    }

    int totalLength = prefix.back();
    int s = 1;
    int e = totalLength;
    int queryMode = rnd.next(5);
    if (queryMode == 0) {
        s = e = rnd.next(1, totalLength);
    } else if (queryMode == 1) {
        int boundary = prefix[rnd.next(1, static_cast<int>(prefix.size()) - 1)];
        s = max(1, boundary - rnd.next(0, 2));
        e = min(totalLength, boundary + rnd.next(0, 2));
    } else if (queryMode == 2) {
        int width = rnd.next(1, min(totalLength, 10));
        s = rnd.next(1, totalLength - width + 1);
        e = s + width - 1;
    } else if (queryMode == 3) {
        s = 1;
        e = rnd.next(1, totalLength);
    } else {
        s = rnd.next(1, totalLength);
        e = totalLength;
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(patterns[i], string(1, symbols[i]));
    }
    println(compressed);
    println(s, e);

    return 0;
}
