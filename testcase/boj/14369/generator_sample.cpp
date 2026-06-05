#include "testlib.h"

#include <algorithm>
#include <array>
#include <string>
#include <vector>

using namespace std;

namespace {

const array<string, 10> kWords = {
    "ZERO", "ONE", "TWO",   "THREE", "FOUR",
    "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
};

int wordLength(const vector<int>& digits) {
    int length = 0;
    for (int digit : digits) {
        length += static_cast<int>(kWords[digit].size());
    }
    return length;
}

string shuffledLetters(vector<int> digits) {
    sort(digits.begin(), digits.end());

    string s;
    for (int digit : digits) {
        s += kWords[digit];
    }
    shuffle(s.begin(), s.end());
    return s;
}

vector<int> singleDigitCase() {
    return {rnd.next(0, 9)};
}

vector<int> repeatedDigitCase() {
    int digit = rnd.next(0, 9);
    int max_count = 20 / static_cast<int>(kWords[digit].size());
    int count = rnd.next(1, max_count);
    return vector<int>(count, digit);
}

vector<int> mixedDigitCase() {
    vector<int> digits;
    int target_length = rnd.next(3, 20);

    while (digits.empty() || wordLength(digits) < 3) {
        int min_digit = digits.empty() ? 0 : digits.back();
        vector<int> candidates;
        for (int digit = min_digit; digit <= 9; ++digit) {
            if (wordLength(digits) + static_cast<int>(kWords[digit].size()) <=
                target_length) {
                candidates.push_back(digit);
            }
        }
        if (candidates.empty()) {
            break;
        }
        digits.push_back(rnd.any(candidates));
    }

    while (rnd.next(0, 2) != 0) {
        vector<int> candidates;
        for (int digit = digits.back(); digit <= 9; ++digit) {
            if (wordLength(digits) + static_cast<int>(kWords[digit].size()) <=
                20) {
                candidates.push_back(digit);
            }
        }
        if (candidates.empty()) {
            break;
        }
        digits.push_back(rnd.any(candidates));
    }

    return digits;
}

vector<int> lengthLimitCase() {
    vector<int> digits;
    int target_length = rnd.next(16, 20);

    while (true) {
        int min_digit = digits.empty() ? 0 : digits.back();
        vector<int> candidates;
        for (int digit = min_digit; digit <= 9; ++digit) {
            int next_length =
                wordLength(digits) + static_cast<int>(kWords[digit].size());
            if (next_length <= target_length) {
                candidates.push_back(digit);
            }
        }
        if (candidates.empty()) {
            break;
        }
        digits.push_back(rnd.any(candidates));
    }

    if (digits.empty()) {
        digits.push_back(rnd.next(0, 9));
    }
    return digits;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 100);
    println(t);

    for (int case_id = 0; case_id < t; ++case_id) {
        int mode = rnd.next(0, 3);
        vector<int> digits;
        if (mode == 0) {
            digits = singleDigitCase();
        } else if (mode == 1) {
            digits = repeatedDigitCase();
        } else if (mode == 2) {
            digits = mixedDigitCase();
        } else {
            digits = lengthLimitCase();
        }
        println(shuffledLetters(digits));
    }

    return 0;
}
