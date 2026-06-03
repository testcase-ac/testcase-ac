#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomLetter() {
    int x = rnd.next(52);
    if (x < 26) return char('a' + x);
    return char('A' + x - 26);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 25);
        s.assign(n, randomLetter());
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        char a = randomLetter();
        char b = randomLetter();
        while (b == a) b = randomLetter();
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? a : b);
    } else if (mode == 2) {
        int pairs = rnd.next(1, 12);
        for (int i = 0; i < pairs; ++i) {
            char c = char('a' + rnd.next(26));
            s += c;
            if (rnd.next(2) == 0) {
                s += char('A' + (c - 'a'));
            } else {
                s += c;
            }
        }
        if (rnd.next(2) == 0) shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        int n = rnd.next(5, 45);
        int alphabetSize = rnd.next(1, 8);
        vector<char> alphabet;
        while ((int)alphabet.size() < alphabetSize) {
            char c = randomLetter();
            bool seen = false;
            for (char existing : alphabet) {
                if (existing == c) seen = true;
            }
            if (!seen) alphabet.push_back(c);
        }
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else if (mode == 4) {
        vector<char> alphabet;
        for (char c = 'a'; c <= 'z'; ++c) alphabet.push_back(c);
        for (char c = 'A'; c <= 'Z'; ++c) alphabet.push_back(c);
        shuffle(alphabet.begin(), alphabet.end());
        int n = rnd.next(20, 52);
        for (int i = 0; i < n; ++i) s += alphabet[i];
    } else {
        int blockCount = rnd.next(2, 8);
        for (int i = 0; i < blockCount; ++i) {
            char c = randomLetter();
            int len = rnd.next(1, 7);
            s.append(len, c);
        }
    }

    println((int)s.size());
    println(s);

    return 0;
}
