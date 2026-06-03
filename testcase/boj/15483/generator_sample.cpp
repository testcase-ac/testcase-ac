#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

void mutateOne(string& s, const string& alphabet) {
    int pos = rnd.next((int)s.size());
    char c = rnd.any(alphabet);
    if (alphabet.size() > 1) {
        while (c == s[pos]) c = rnd.any(alphabet);
    }
    s[pos] = c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> alphabets = {"ab", "abc", "abcd", "aeiou", "abcdefghijklmnopqrstuvwxyz"};
    string alphabet = rnd.any(alphabets);
    int mode = rnd.next(0, 6);

    string a, b;
    if (mode == 0) {
        int len = rnd.next(1, 25);
        a = randomString(len, alphabet);
        b = a;
    } else if (mode == 1) {
        int len = rnd.next(1, 25);
        a = randomString(len, alphabet);
        b = a;
        int changes = rnd.next(1, min(6, len));
        for (int i = 0; i < changes; ++i) mutateOne(b, alphabet);
    } else if (mode == 2) {
        int common = rnd.next(1, 15);
        int extra = rnd.next(1, 10);
        string core = randomString(common, alphabet);
        a = core;
        b = core + randomString(extra, alphabet);
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 3) {
        int left = rnd.next(1, 12);
        int mid = rnd.next(1, 8);
        int right = rnd.next(1, 12);
        string prefix = randomString(left, alphabet);
        string suffix = randomString(right, alphabet);
        a = prefix + randomString(mid, alphabet) + suffix;
        b = prefix + randomString(mid, alphabet) + suffix;
    } else if (mode == 4) {
        int len = rnd.next(2, 30);
        a = randomString(len, alphabet);
        b = a;
        reverse(b.begin(), b.end());
    } else if (mode == 5) {
        int lenA = rnd.next(1, 30);
        int lenB = rnd.next(1, 30);
        a = randomString(lenA, alphabet);
        b = randomString(lenB, alphabet);
    } else {
        int blockLen = rnd.next(1, 4);
        int repeatA = rnd.next(6, 25);
        int repeatB = rnd.next(6, 25);
        string block = randomString(blockLen, alphabet);
        for (int i = 0; i < repeatA; ++i) a += block;
        for (int i = 0; i < repeatB; ++i) b += block;
        int changes = rnd.next(1, min(8, (int)b.size()));
        for (int i = 0; i < changes; ++i) mutateOne(b, alphabet);
    }

    println(a);
    println(b);
    return 0;
}
