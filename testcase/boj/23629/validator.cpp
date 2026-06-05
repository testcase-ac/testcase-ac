#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct DigitWord {
    string word;
    int digit;
};

const vector<DigitWord> DIGIT_WORDS = {
    {"ZERO", 0}, {"ONE", 1},   {"TWO", 2},   {"THREE", 3}, {"FOUR", 4},
    {"FIVE", 5}, {"SIX", 6},   {"SEVEN", 7}, {"EIGHT", 8}, {"NINE", 9},
};

bool startsWith(const string& s, int pos, const string& prefix) {
    return pos + static_cast<int>(prefix.size()) <= static_cast<int>(s.size()) &&
           s.compare(pos, prefix.size(), prefix) == 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == 'x' || c == '/' || c == '=';
}

void validateDecodableSegmentIfAny(const string& segment, int start_pos) {
    long long value = 0;
    int pos = 0;

    while (pos < static_cast<int>(segment.size())) {
        bool matched = false;
        for (const DigitWord& digit_word : DIGIT_WORDS) {
            if (startsWith(segment, pos, digit_word.word)) {
                value = value * 10 + digit_word.digit;
                pos += digit_word.word.size();
                matched = true;
                break;
            }
        }

        if (!matched) {
            return;
        }
    }

    // CHECK: Strings with no possible expression are valid, but a fully
    // digit-word-decodable segment is treated as a stated contained number.
    ensuref(1 <= value && value <= 1000000,
            "decoded number at position %d is out of range: %lld", start_pos + 1, value);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[A-Z+\\-/x=]{4,100000}", "S");

    ensuref(s.back() == '=', "S must end with '='");

    int equals_count = 0;
    for (char c : s) {
        if (c == '=') {
            ++equals_count;
        }
    }
    ensuref(equals_count == 1, "'=' must appear exactly once");

    ensuref(!isOperator(s[0]), "S must not start with an operator");
    ensuref(!startsWith(s, 0, "ZERO"), "ZERO must not appear at the start of S");

    int segment_start = 0;
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        if (!isOperator(s[i])) {
            continue;
        }

        if (segment_start < i) {
            validateDecodableSegmentIfAny(s.substr(segment_start, i - segment_start),
                                          segment_start);
        }

        if (s[i] != '=' && startsWith(s, i + 1, "ZERO")) {
            ensuref(false, "ZERO must not appear immediately after operator at position %d",
                    i + 1);
        }

        segment_start = i + 1;
    }

    inf.readEof();
}
