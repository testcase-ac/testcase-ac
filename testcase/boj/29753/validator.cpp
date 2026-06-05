#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int parseGpaCents(const string& token) {
    ensuref(!token.empty(), "X is empty");

    size_t dot = token.find('.');
    string whole = dot == string::npos ? token : token.substr(0, dot);
    string frac = dot == string::npos ? "" : token.substr(dot + 1);

    ensuref(token.find('.', dot == string::npos ? 0 : dot + 1) == string::npos,
            "X has multiple decimal points: %s", token.c_str());
    ensuref(!whole.empty(), "X has no integer part: %s", token.c_str());
    ensuref(whole.size() == 1, "X integer part must be one digit: %s", token.c_str());
    ensuref('0' <= whole[0] && whole[0] <= '4', "X integer part out of range: %s", token.c_str());
    ensuref(frac.size() <= 2, "X has more than two decimal places: %s", token.c_str());

    int cents = (whole[0] - '0') * 100;
    if (!frac.empty()) {
        for (char ch : frac) {
            ensuref('0' <= ch && ch <= '9', "X fractional part is not numeric: %s", token.c_str());
        }
        cents += (frac[0] - '0') * 10;
        if (frac.size() == 2) {
            cents += frac[1] - '0';
        }
    }

    ensuref(0 <= cents && cents <= 450, "X is out of range: %s", token.c_str());
    return cents;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<string> grades = {"A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F"};

    int n = inf.readInt(2, 24, "N");
    inf.readSpace();
    string x = inf.readToken("[^ ]+", "X");
    parseGpaCents(x);
    inf.readEoln();

    for (int i = 1; i <= n - 1; ++i) {
        inf.readInt(1, 6, "c_i");
        inf.readSpace();
        string grade = inf.readToken("[A-DF][+0]?", "g_i");
        ensuref(find(grades.begin(), grades.end(), grade) != grades.end(),
                "invalid grade at course %d: %s", i, grade.c_str());
        inf.readEoln();
    }

    inf.readInt(1, 6, "L");
    inf.readEoln();
    inf.readEof();
}
