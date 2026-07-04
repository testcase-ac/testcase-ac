#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomLetter(const string& alphabet) {
    return alphabet[rnd.next(static_cast<int>(alphabet.size()))];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 80);
    string s;

    if (mode == 0) {
        int alphabetSize = rnd.next(1, 26);
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        alphabet.resize(alphabetSize);
        for (int i = 0; i < n; ++i) {
            s += randomLetter(alphabet);
        }
    } else if (mode == 1) {
        char c = rnd.next('A', 'Z');
        s.assign(n, c);
    } else if (mode == 2) {
        char a = rnd.next('A', 'Z');
        char b = rnd.next('A', 'Z');
        if (a == b) b = static_cast<char>('A' + (b - 'A' + 1) % 26);
        for (int i = 0; i < n; ++i) {
            s += (i % 2 == 0 ? a : b);
        }
    } else if (mode == 3) {
        int period = rnd.next(1, 8);
        string base;
        for (int i = 0; i < period; ++i) {
            base += rnd.next('A', 'Z');
        }
        for (int i = 0; i < n; ++i) {
            s += base[i % period];
        }
    } else if (mode == 4) {
        int half = (n + 1) / 2;
        string alphabet = "ABCDEF";
        for (int i = 0; i < half; ++i) {
            s += randomLetter(alphabet);
        }
        for (int i = n / 2 - 1; i >= 0; --i) {
            s += s[i];
        }
    } else if (mode == 5) {
        string block;
        int blockLen = rnd.next(1, 10);
        for (int i = 0; i < blockLen; ++i) {
            block += rnd.next('A', 'Z');
        }
        while (static_cast<int>(s.size()) < n) {
            s += block;
            if (rnd.next(0, 4) == 0) {
                s += rnd.next('A', 'Z');
            }
        }
        s.resize(n);
    } else {
        vector<string> prefixes = {"ENDED", "ERROR", "ABABA", "AAAAAB", "ABCABC"};
        s = prefixes[rnd.next(static_cast<int>(prefixes.size()))];
        while (static_cast<int>(s.size()) < n) {
            s += rnd.next('A', 'Z');
        }
        s.resize(n);
    }

    println(s);
    return 0;
}
