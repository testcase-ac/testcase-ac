#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomLetter() {
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return rnd.any(letters);
}

char differentLetter(char c) {
    char x = randomLetter();
    while (x == c) x = randomLetter();
    return x;
}

string randomString(int len, bool sameLetter = false) {
    string s;
    if (sameLetter) {
        char c = randomLetter();
        return string(len, c);
    }
    for (int i = 0; i < len; ++i) s += randomLetter();
    return s;
}

string withExtras(const string& expected, int extraCount) {
    string produced;
    for (char c : expected) {
        int before = rnd.next(0, extraCount);
        before = min(before, extraCount);
        for (int i = 0; i < before; ++i) produced += randomLetter();
        extraCount -= before;
        produced += c;
    }
    for (int i = 0; i < extraCount; ++i) produced += randomLetter();
    return produced;
}

pair<string, string> makeCase(int mode) {
    if (mode == 0) {
        int len = rnd.next(1, 8);
        string expected = randomString(len);
        return {expected, withExtras(expected, rnd.next(0, 8))};
    }

    if (mode == 1) {
        int len = rnd.next(1, 12);
        string expected = randomString(len, true);
        return {expected, withExtras(expected, rnd.next(0, 10))};
    }

    if (mode == 2) {
        int len = rnd.next(2, 10);
        string expected = randomString(len);
        int removeAt = rnd.next(0, len - 1);
        string produced;
        for (int i = 0; i < len; ++i) {
            if (i == removeAt) continue;
            produced += expected[i];
            if (rnd.next(0, 1)) produced += randomLetter();
        }
        if (produced.empty()) produced = string(1, differentLetter(expected[removeAt]));
        return {expected, produced};
    }

    if (mode == 3) {
        int len = rnd.next(1, 9);
        string expected = randomString(len);
        string produced = expected;
        int changeAt = rnd.next(0, len - 1);
        produced[changeAt] = differentLetter(expected[changeAt]);
        if (rnd.next(0, 1)) produced = withExtras(produced, rnd.next(1, 5));
        return {expected, produced};
    }

    if (mode == 4) {
        string expected = "Aa";
        int repeats = rnd.next(1, 5);
        string produced;
        for (int i = 0; i < repeats; ++i) produced += "aA";
        if (rnd.next(0, 1)) produced += expected;
        return {expected, produced};
    }

    int len = rnd.next(1, 12);
    string expected = randomString(len);
    string produced = expected;
    if (rnd.next(0, 1)) shuffle(produced.begin(), produced.end());
    return {expected, produced};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 18);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        auto [expected, produced] = makeCase(rnd.next(0, 5));
        println(expected);
        println(produced);
    }

    return 0;
}
