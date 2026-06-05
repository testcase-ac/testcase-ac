#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string word;
    for (int i = 0; i < len; ++i) {
        word += rnd.any(alphabet);
    }
    return word;
}

string numberToWord(long long value, const vector<char>& digitLetter) {
    string digits = to_string(value);
    string word;
    for (char digit : digits) {
        word += digitLetter[digit - '0'];
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<char> letters;
    for (char c = 'A'; c <= 'Z'; ++c) {
        letters.push_back(c);
    }
    shuffle(letters.begin(), letters.end());

    int mode = rnd.next(0, 5);
    string first, second, result;

    if (mode <= 1) {
        vector<char> digitLetter(10);
        for (int digit = 0; digit < 10; ++digit) {
            digitLetter[digit] = letters[digit];
        }

        int limitMode = rnd.next(0, 2);
        long long upper = limitMode == 0 ? 9999LL : (limitMode == 1 ? 999999999LL : 99999999999999999LL);
        long long a = rnd.next(0LL, upper);
        long long b = rnd.next(0LL, upper);
        if (a + b > 999999999999999999LL) {
            b = 999999999999999999LL - a;
        }

        first = numberToWord(a, digitLetter);
        second = numberToWord(b, digitLetter);
        result = numberToWord(a + b, digitLetter);
    } else if (mode == 2) {
        int uniqueCount = rnd.next(11, 18);
        string alphabet(letters.begin(), letters.begin() + uniqueCount);
        first = alphabet.substr(0, rnd.next(4, 8));
        second = alphabet.substr(rnd.next(1, 4), rnd.next(4, 8));
        result = alphabet.substr(uniqueCount - rnd.next(4, 8));
    } else if (mode == 3) {
        char a = letters[0], b = letters[1], c = letters[2];
        int len = rnd.next(1, 18);
        first = string(len, a);
        second = string(rnd.next(1, len), b);
        result = string(rnd.next(len, 18), c);
    } else {
        int alphabetSize = rnd.next(1, 10);
        string alphabet(letters.begin(), letters.begin() + alphabetSize);
        int maxLen = rnd.next(1, 18);
        first = randomWord(rnd.next(1, maxLen), alphabet);
        second = randomWord(rnd.next(1, maxLen), alphabet);
        result = randomWord(rnd.next(1, maxLen), alphabet);
    }

    println(first, second, result);
    return 0;
}
