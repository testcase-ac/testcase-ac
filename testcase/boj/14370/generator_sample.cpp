#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

namespace {

const vector<string> DIGIT_WORDS = {
    "ZERO", "ONE", "TWO", "THREE", "FOUR",
    "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
};

string makeCase(const vector<int>& counts) {
    string s;
    for (int digit = 0; digit < 10; ++digit) {
        for (int i = 0; i < counts[digit]; ++i) {
            s += DIGIT_WORDS[digit];
        }
    }
    shuffle(s.begin(), s.end());
    return s;
}

vector<int> sparseCounts(int targetDigits) {
    vector<int> counts(10);
    int active = rnd.next(1, min(10, targetDigits));
    vector<int> digits;
    for (int digit = 0; digit < 10; ++digit) {
        digits.push_back(digit);
    }
    shuffle(digits.begin(), digits.end());

    for (int i = 0; i < active; ++i) {
        counts[digits[i]] = 1;
    }
    for (int i = active; i < targetDigits; ++i) {
        counts[digits[rnd.next(active)]]++;
    }
    return counts;
}

vector<int> modeCounts(int mode) {
    vector<int> counts(10);

    if (mode == 0) {
        counts[rnd.next(10)] = rnd.next(1, 20);
    } else if (mode == 1) {
        for (int digit = 0; digit < 10; ++digit) {
            counts[digit] = rnd.next(1, 5);
        }
    } else if (mode == 2) {
        int parity = rnd.next(2);
        for (int digit = parity; digit < 10; digit += 2) {
            counts[digit] = rnd.next(1, 12);
        }
        counts[rnd.next(10)] += rnd.next(0, 4);
    } else if (mode == 3) {
        int targetDigits = rnd.next(80, 220);
        counts = sparseCounts(targetDigits);
    } else {
        int targetDigits = rnd.next(1, 45);
        counts = sparseCounts(targetDigits);
    }

    return counts;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 30);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(5);
        string s = makeCase(modeCounts(mode));
        println(s);
    }

    return 0;
}
