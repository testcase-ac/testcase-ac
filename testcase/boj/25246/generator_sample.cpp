#include "testlib.h"

#include <string>

using namespace std;

char randomConsonant() {
    static const string consonants = "bcdfghjklmnpqrstvwxyz";
    return rnd.any(consonants);
}

char randomVowel() {
    static const string vowels = "aeiou";
    return rnd.any(vowels);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(45, 50);
    } else {
        n = rnd.next(2, 30);
    }

    string s(n, 'a');
    for (int i = 0; i < n; ++i) {
        s[i] = rnd.next(0, 4) == 0 ? randomVowel() : randomConsonant();
    }

    int vowelPos;
    if (mode == 2) {
        vowelPos = 0;
    } else if (mode == 3) {
        vowelPos = n - 1;
    } else {
        vowelPos = rnd.next(0, n - 1);
    }
    s[vowelPos] = randomVowel();

    if (mode == 4 && n > 1) {
        s[0] = rnd.next(0, 1) == 0 ? randomConsonant() : randomVowel();
        s[0] = char(s[0] - 'a' + 'A');
        if (vowelPos == 0) {
            s[rnd.next(1, n - 1)] = randomVowel();
        }
    } else if (n > 1 && rnd.next(0, 4) == 0) {
        s[0] = char(s[0] - 'a' + 'A');
        if (vowelPos == 0) {
            s[rnd.next(1, n - 1)] = randomVowel();
        }
    }

    println(s);
    return 0;
}
