#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

const string kMaxN = "100000000000000000000";

string randomDigits(int length, int maxDigit) {
    string s;
    s.reserve(length);
    s.push_back(char('1' + rnd.next(min(8, maxDigit))));
    for (int i = 1; i < length; ++i) {
        s.push_back(char('0' + rnd.next(maxDigit + 1)));
    }
    return s;
}

string nonIncreasingDigits(int length) {
    vector<char> digits;
    digits.reserve(length);
    digits.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < length; ++i) {
        digits.push_back(char('0' + rnd.next(10)));
    }
    sort(digits.begin(), digits.end(), greater<char>());
    return string(digits.begin(), digits.end());
}

string zeroHeavyDigits(int length) {
    string s(length, '0');
    s[0] = char('1' + rnd.next(9));
    int nonzeroCount = rnd.next(1, min(length, 4));
    for (int i = 0; i < nonzeroCount; ++i) {
        int pos = rnd.next(length);
        s[pos] = char('1' + rnd.next(9));
    }
    if (s[0] == '0') s[0] = char('1' + rnd.next(9));
    return s;
}

string repeatedDigits(int length) {
    string alphabet = "0123456789";
    shuffle(alphabet.begin(), alphabet.end());
    int kinds = rnd.next(1, min(4, length));

    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) s.push_back(alphabet[rnd.next(kinds)]);
    if (s[0] == '0') s[0] = char('1' + rnd.next(9));
    return s;
}

string makeCase() {
    int mode = rnd.next(8);
    if (mode == 0) return to_string(rnd.next(1, 9));
    if (mode == 1) return kMaxN;

    int length = 0;
    if (mode == 2) {
        length = rnd.next(2, 6);
        return nonIncreasingDigits(length);
    }
    if (mode == 3) {
        length = rnd.next(2, 20);
        return zeroHeavyDigits(length);
    }
    if (mode == 4) {
        length = rnd.next(2, 20);
        return repeatedDigits(length);
    }
    if (mode == 5) {
        length = 20;
        return randomDigits(length, rnd.next(1, 9));
    }

    length = rnd.next(2, 18);
    string s = randomDigits(length, 9);
    if (mode == 6 && length >= 2) {
        int pos = rnd.next(1, length - 1);
        s[pos] = char(max<int>('0', s[pos - 1] - 1));
    }
    return s;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 35);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println(makeCase());
    }

    return 0;
}
