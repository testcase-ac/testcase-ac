#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

const string kVowels = "AEIOUaeiou";
const string kConsonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
const string kLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char anyFrom(const string& chars) {
    return chars[rnd.next(static_cast<int>(chars.size()))];
}

string randomLetters(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(anyFrom(kLetters));
    }
    return s;
}

string alternatingPattern(int n, bool startWithVowel) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        bool needVowel = (i % 2 == 0) == startWithVowel;
        s.push_back(anyFrom(needVowel ? kVowels : kConsonants));
    }
    return s;
}

string mostlyRepeated(int n) {
    string pool;
    int poolSize = rnd.next(1, 6);
    for (int i = 0; i < poolSize; ++i) {
        pool.push_back(anyFrom(kLetters));
    }

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(pool[rnd.next(poolSize)]);
    }
    return s;
}

string shuffledBlocks(int n) {
    vector<char> chars;
    chars.reserve(n);

    while (static_cast<int>(chars.size()) < n) {
        int blockType = rnd.next(0, 3);
        int blockLen = rnd.next(1, min(10, n - static_cast<int>(chars.size())));
        const string& alphabet = blockType == 0 ? kVowels : (blockType == 1 ? kConsonants : kLetters);
        for (int i = 0; i < blockLen; ++i) {
            chars.push_back(anyFrom(alphabet));
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(chars.begin(), chars.end());
    }

    return string(chars.begin(), chars.end());
}

} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 5) {
        n = rnd.next(80, 180);
    } else {
        n = rnd.next(6, 60);
    }

    string s;
    if (mode == 0) {
        s = randomLetters(n);
    } else if (mode == 1) {
        s = alternatingPattern(n, true);
    } else if (mode == 2) {
        s = alternatingPattern(n, false);
    } else if (mode == 3) {
        s = mostlyRepeated(n);
    } else if (mode == 4) {
        s = shuffledBlocks(n);
    } else {
        s = randomLetters(n);
    }

    println(s);
    return 0;
}
