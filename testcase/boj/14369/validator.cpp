#include "testlib.h"

#include <array>
#include <string>

using namespace std;

namespace {

const array<string, 10> kWords = {
    "ZERO", "ONE", "TWO",   "THREE", "FOUR",
    "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
};

const array<int, 10> kOrder = {0, 2, 8, 6, 4, 5, 7, 1, 9, 3};
const array<char, 10> kUnique = {'Z', 'W', 'G', 'X', 'U',
                                 'F', 'S', 'O', 'N', 'T'};

bool hasDigitWordDecomposition(const string& s) {
    array<int, 26> counts{};
    for (char ch : s) {
        counts[ch - 'A']++;
    }

    for (int i = 0; i < 10; ++i) {
        int digit = kOrder[i];
        int times = counts[kUnique[i] - 'A'];
        if (digit == 9) {
            if (times % 2 != 0) {
                return false;
            }
            times /= 2;
        }
        if (times < 0) {
            return false;
        }
        for (char ch : kWords[digit]) {
            counts[ch - 'A'] -= times;
            if (counts[ch - 'A'] < 0) {
                return false;
            }
        }
    }

    for (int count : counts) {
        if (count != 0) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);
        string s = inf.readToken("[A-Z]{3,20}", "S");
        inf.readEoln();

        ensuref(hasDigitWordDecomposition(s),
                "S must be a shuffled spelling of a nondecreasing digit string");
    }

    inf.readEof();
}
