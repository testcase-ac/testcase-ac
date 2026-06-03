#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char randomVowel() {
    return rnd.any(string("aeiou"));
}

char randomConsonant() {
    return rnd.any(string("bcdfghjklmnpqrstvwxyz"));
}

string makeBaseWord(int n) {
    string s(n, 'a');
    s[0] = rnd.next(2) ? randomConsonant() : randomVowel();
    s[n - 1] = rnd.next(2) ? randomConsonant() : randomVowel();

    int style = rnd.next(4);
    for (int i = 1; i + 1 < n; ++i) {
        if (style == 0) {
            s[i] = randomVowel();
        } else if (style == 1) {
            s[i] = randomConsonant();
        } else if (style == 2) {
            s[i] = (i % 2 == 0) ? randomVowel() : randomConsonant();
        } else {
            s[i] = rnd.next(100) < 55 ? randomVowel() : randomConsonant();
        }
    }
    return s;
}

string duramuriShuffle(const string& s) {
    string t = s;
    vector<int> vowelPositions;
    vector<char> vowels;

    for (int i = 1; i + 1 < (int)s.size(); ++i) {
        if (isVowel(s[i])) {
            vowelPositions.push_back(i);
            vowels.push_back(s[i]);
        }
    }

    shuffle(vowels.begin(), vowels.end());
    for (int i = 0; i < (int)vowelPositions.size(); ++i) {
        t[vowelPositions[i]] = vowels[i];
    }
    return t;
}

char differentLowercase(char c) {
    char next = (char)rnd.next((int)'a', (int)'z');
    while (next == c) {
        next = (char)rnd.next((int)'a', (int)'z');
    }
    return next;
}

char differentConsonant(char c) {
    char next = randomConsonant();
    while (next == c) {
        next = randomConsonant();
    }
    return next;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 30);
    if (rnd.next(10) == 0) {
        n = rnd.next(31, 80);
    }

    string first = makeBaseWord(n);
    string second = duramuriShuffle(first);

    if (mode == 1) {
        int pos = rnd.next(2) ? 0 : n - 1;
        second[pos] = differentLowercase(first[pos]);
    } else if (mode == 2) {
        int pos = rnd.next(n);
        second[pos] = isVowel(second[pos]) ? randomConsonant() : randomVowel();
    } else if (mode == 3) {
        vector<int> consonantPositions;
        for (int i = 1; i + 1 < n; ++i) {
            if (!isVowel(second[i])) {
                consonantPositions.push_back(i);
            }
        }
        if (consonantPositions.empty()) {
            if (n == 2) {
                n = 3;
                first = makeBaseWord(n);
                second = duramuriShuffle(first);
            }
            int pos = rnd.next(1, n - 2);
            first[pos] = randomConsonant();
            second = duramuriShuffle(first);
            consonantPositions.push_back(pos);
        }
        int pos = rnd.any(consonantPositions);
        second[pos] = differentConsonant(second[pos]);
    } else if (mode == 4) {
        vector<int> positions;
        for (int i = 1; i + 1 < n; ++i) {
            positions.push_back(i);
        }
        if (!positions.empty()) {
            shuffle(positions.begin(), positions.end());
            int a = positions[0];
            int b = positions.size() >= 2 ? positions[1] : positions[0];
            second[a] = randomVowel();
            second[b] = randomVowel();
        }
    }

    println(n);
    println(first);
    println(second);

    return 0;
}
