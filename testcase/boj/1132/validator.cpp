#include "testlib.h"
#include <set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    set<char> allowed_letters;
    for (char c = 'A'; c <= 'J'; ++c) allowed_letters.insert(c);

    vector<string> numbers;
    set<char> used_letters;
    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[A-J]{1,12}", "number");
        inf.readEoln();

        // Check length
        ensuref(1 <= (int)s.size() && (int)s.size() <= 12, 
            "Number at line %d has invalid length %d", i+2, (int)s.size());

        // Check all characters are A-J
        for (int j = 0; j < (int)s.size(); ++j) {
            ensuref(allowed_letters.count(s[j]), 
                "Invalid character '%c' at line %d, position %d", s[j], i+2, j+1);
            used_letters.insert(s[j]);
        }

        // Check first character is not '0' (by problem, first char is always a letter, so this is always true)
        // But we must check: "적어도 한 알파벳은 수의 가장 처음에 주어지지 않는다."
        // Translation: "At least one alphabet is not given at the first position of a number."
        // But this is a negative statement: "At least one alphabet is not at the first position" -- but all digits are alphabets.
        // But the sample input and problem context: Each digit is always a letter, and the only restriction is that no number starts with '0' (i.e., after mapping, no letter mapped to 0 can be at the first position of any number).
        // So, for validator, we do not check this here, but the solution must ensure that in mapping.

        numbers.push_back(s);
    }

    // Check that all digits in all numbers are from 'A' to 'J'
    for (const string& s : numbers) {
        for (char c : s) {
            ensuref(allowed_letters.count(c), "Invalid character '%c' in number '%s'", c, s.c_str());
        }
    }

    // Check that no number has leading zeros (not possible here, as all are letters)
    // But we must check that at least one letter is not at the first position of any number.
    // Let's check: For each letter, is there at least one number where it is not at the first position?
    // But the statement says: "적어도 한 알파벳은 수의 가장 처음에 주어지지 않는다."
    // Translation: "At least one alphabet is not given at the first position of a number."
    // That is, there exists at least one letter that is never the first character of any number.

    set<char> first_letters;
    for (const string& s : numbers) {
        first_letters.insert(s[0]);
    }
    bool found = false;
    for (char c : used_letters) {
        if (!first_letters.count(c)) {
            found = true;
            break;
        }
    }
    ensuref(found, "There must be at least one letter that is never the first character of any number.");

    inf.readEof();
}
