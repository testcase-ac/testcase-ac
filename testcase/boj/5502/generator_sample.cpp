#include "testlib.h"

#include <string>

using namespace std;

char randomChar(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += randomChar(alphabet);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string digits = "0123456789";
    const string alphaNum = upper + lower + digits;
    const string compact = "Aa0Bb1";

    int mode = rnd.next(6);
    int n = rnd.next(3, 30);
    string s;

    if (mode == 0) {
        s = randomString(n, compact);
        for (int i = 0; i < n / 2; ++i) s[n - 1 - i] = s[i];
    } else if (mode == 1) {
        s = randomString(n, compact);
        for (int i = 0; i < n / 2; ++i) s[n - 1 - i] = s[i];
        int edits = rnd.next(1, 3);
        for (int i = 0; i < edits; ++i) {
            int pos = rnd.next(n);
            char c = randomChar(alphaNum);
            while (c == s[pos]) c = randomChar(alphaNum);
            s[pos] = c;
        }
    } else if (mode == 2) {
        int alphabetSize = rnd.next(2, 6);
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += compact[rnd.next(alphabetSize)];
    } else if (mode == 3) {
        int patternLen = rnd.next(2, 5);
        string pattern = randomString(patternLen, compact);
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += pattern[i % patternLen];
    } else if (mode == 4) {
        string classes[] = {upper, lower, digits, compact};
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += randomChar(classes[i % 4]);
    } else {
        s = randomString(n, alphaNum);
    }

    println(n);
    println(s);
    return 0;
}
