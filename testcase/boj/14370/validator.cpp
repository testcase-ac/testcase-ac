#include "testlib.h"
#include <array>
#include <string>
#include <vector>
using namespace std;

namespace {

const vector<string> DIGIT_WORDS = {
    "ZERO", "ONE", "TWO", "THREE", "FOUR",
    "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
};

void subtractWord(array<int, 26>& freq, const string& word, int count) {
    for (char ch : word) {
        freq[ch - 'A'] -= count;
    }
}

void validateDecodable(const string& s, int caseIndex) {
    array<int, 26> freq{};
    for (char ch : s) {
        ++freq[ch - 'A'];
    }

    array<int, 10> digits{};
    digits[0] = freq['Z' - 'A'];
    subtractWord(freq, DIGIT_WORDS[0], digits[0]);
    digits[2] = freq['W' - 'A'];
    subtractWord(freq, DIGIT_WORDS[2], digits[2]);
    digits[4] = freq['U' - 'A'];
    subtractWord(freq, DIGIT_WORDS[4], digits[4]);
    digits[6] = freq['X' - 'A'];
    subtractWord(freq, DIGIT_WORDS[6], digits[6]);
    digits[8] = freq['G' - 'A'];
    subtractWord(freq, DIGIT_WORDS[8], digits[8]);
    digits[1] = freq['O' - 'A'];
    subtractWord(freq, DIGIT_WORDS[1], digits[1]);
    digits[3] = freq['H' - 'A'];
    subtractWord(freq, DIGIT_WORDS[3], digits[3]);
    digits[5] = freq['F' - 'A'];
    subtractWord(freq, DIGIT_WORDS[5], digits[5]);
    digits[7] = freq['S' - 'A'];
    subtractWord(freq, DIGIT_WORDS[7], digits[7]);
    digits[9] = freq['I' - 'A'];
    subtractWord(freq, DIGIT_WORDS[9], digits[9]);

    for (int digit = 0; digit < 10; ++digit) {
        ensuref(digits[digit] >= 0, "case %d has negative count for digit %d",
                caseIndex, digit);
    }
    for (int letter = 0; letter < 26; ++letter) {
        ensuref(freq[letter] == 0, "case %d leaves unmatched letter %c count %d",
                caseIndex, char('A' + letter), freq[letter]);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        string s = inf.readToken("[A-Z]{3,2000}", "S");
        inf.readEoln();
        validateDecodable(s, tc);
    }

    inf.readEof();
    return 0;
}
