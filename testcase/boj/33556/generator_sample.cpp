#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

string randomToken(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string randomNonNullToken(int len, const string& alphabet) {
    while (true) {
        string s = randomToken(len, alphabet);
        if (s != "null") return s;
    }
}

string toggleSomeLetters(string s) {
    bool changed = false;
    for (char& c : s) {
        if (!isalpha(static_cast<unsigned char>(c))) continue;
        if (rnd.next(2) == 0) {
            c = islower(static_cast<unsigned char>(c))
                    ? static_cast<char>(toupper(static_cast<unsigned char>(c)))
                    : static_cast<char>(tolower(static_cast<unsigned char>(c)));
            changed = true;
        }
    }

    if (!changed) {
        for (char& c : s) {
            if (!isalpha(static_cast<unsigned char>(c))) continue;
            c = islower(static_cast<unsigned char>(c))
                    ? static_cast<char>(toupper(static_cast<unsigned char>(c)))
                    : static_cast<char>(tolower(static_cast<unsigned char>(c)));
            break;
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string alnum = lower + upper + digits;
    const string letterDigit = "abcxyzABCXYZ0123456789";

    int mode = rnd.next(8);
    int len = rnd.next(1, 24);
    string a;
    string b;

    if (mode == 0) {
        a = randomNonNullToken(len, letterDigit);
        b = a;
    } else if (mode == 1) {
        a = randomNonNullToken(rnd.next(1, 16), lower + digits);
        if (none_of(a.begin(), a.end(), [](char c) { return isalpha(static_cast<unsigned char>(c)); })) {
            a[rnd.next((int)a.size())] = rnd.any(lower);
        }
        b = toggleSomeLetters(a);
    } else if (mode == 2) {
        a = "null";
        b = randomNonNullToken(rnd.next(1, 20), alnum);
    } else if (mode == 3) {
        a = randomNonNullToken(rnd.next(1, 20), alnum);
        b = "null";
    } else if (mode == 4) {
        a = "null";
        b = "null";
    } else if (mode == 5) {
        int lenA = rnd.next(1, 15);
        int lenB = rnd.next(1, 15);
        if (lenA == lenB) ++lenB;
        a = randomNonNullToken(lenA, alnum);
        b = randomNonNullToken(lenB, alnum);
    } else if (mode == 6) {
        int longLen = rnd.next(30, 100);
        a = randomNonNullToken(longLen, digits + lower);
        b = randomNonNullToken(longLen, digits + upper);
    } else {
        a = randomNonNullToken(rnd.next(1, 100), alnum);
        b = randomNonNullToken(rnd.next(1, 100), alnum);
    }

    println(a);
    println(b);
    return 0;
}
