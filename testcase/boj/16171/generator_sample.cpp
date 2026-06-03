#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

char randomLetter() {
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return rnd.any(letters);
}

char randomDigit() {
    return char('0' + rnd.next(10));
}

string randomLetters(int length) {
    string result;
    for (int i = 0; i < length; ++i) {
        result += randomLetter();
    }
    return result;
}

string withRandomDigits(const string& letters, int maxDigitsBetween, bool allowEnds) {
    string result;
    if (allowEnds) {
        int prefixDigits = rnd.next(0, maxDigitsBetween);
        for (int i = 0; i < prefixDigits; ++i) {
            result += randomDigit();
        }
    }

    for (char ch : letters) {
        result += ch;
        int digits = rnd.next(0, maxDigitsBetween);
        for (int i = 0; i < digits; ++i) {
            result += randomDigit();
        }
    }

    return result;
}

string trimToLimitKeepingLetters(const string& s, int limit) {
    string result = s.substr(0, limit);
    while (!result.empty() && isdigit(result.back())) {
        result.pop_back();
    }
    return result.empty() ? string(1, randomLetter()) : result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string letters;
    string k;

    if (mode == 0) {
        // Present keyword with digits inserted between every letter.
        k = randomLetters(rnd.next(1, 18));
        letters = randomLetters(rnd.next(0, 5)) + k + randomLetters(rnd.next(0, 5));
    } else if (mode == 1) {
        // Present keyword at an edge after removing digits.
        k = randomLetters(rnd.next(1, 20));
        bool atFront = rnd.next(2) == 0;
        letters = atFront ? k + randomLetters(rnd.next(0, 8))
                          : randomLetters(rnd.next(0, 8)) + k;
    } else if (mode == 2) {
        // Near miss: one character is changed, so the keyword should not match.
        k = randomLetters(rnd.next(2, 18));
        letters = k;
        int pos = rnd.next(int(letters.size()));
        char replacement = randomLetter();
        while (replacement == letters[pos]) {
            replacement = randomLetter();
        }
        letters[pos] = replacement;
        letters = randomLetters(rnd.next(0, 5)) + letters + randomLetters(rnd.next(0, 5));
    } else if (mode == 3) {
        // Case-sensitive mismatch around otherwise similar text.
        k = randomLetters(rnd.next(1, 18));
        letters = k;
        int pos = rnd.next(int(letters.size()));
        if (letters[pos] >= 'a' && letters[pos] <= 'z') {
            letters[pos] = char(letters[pos] - 'a' + 'A');
        } else {
            letters[pos] = char(letters[pos] - 'A' + 'a');
        }
        letters = randomLetters(rnd.next(0, 5)) + letters + randomLetters(rnd.next(0, 5));
    } else if (mode == 4) {
        // Single-character keyword with a short, digit-heavy textbook string.
        k = string(1, randomLetter());
        letters = randomLetters(rnd.next(1, 6));
        if (rnd.next(2) == 0) {
            letters[rnd.next(int(letters.size()))] = k[0];
        }
    } else {
        // Medium random letters and a random substring-sized keyword.
        letters = randomLetters(rnd.next(8, 30));
        int start = rnd.next(int(letters.size()));
        int len = rnd.next(1, int(letters.size()) - start);
        k = letters.substr(start, len);
        if (rnd.next(3) == 0) {
            shuffle(k.begin(), k.end());
        }
    }

    int maxDigitsBetween = rnd.next(0, 4);
    string s = withRandomDigits(letters, maxDigitsBetween, true);
    s = trimToLimitKeepingLetters(s, 100);

    if (int(k.size()) > int(s.size())) {
        k.resize(s.size());
    }

    println(s);
    println(k);

    return 0;
}
