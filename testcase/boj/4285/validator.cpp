#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static vector<string> splitStrictLine(const string& line, const string& label) {
    ensuref(!line.empty(), "%s must not be empty", label.c_str());
    ensuref(line.front() != ' ' && line.back() != ' ',
            "%s must not have leading or trailing spaces", label.c_str());

    vector<string> tokens;
    string token;
    for (char ch : line) {
        if (ch == ' ') {
            ensuref(!token.empty(), "%s must not contain repeated spaces", label.c_str());
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(ch);
        }
    }
    ensuref(!token.empty(), "%s must not end with a space", label.c_str());
    tokens.push_back(token);
    return tokens;
}

static void ensureCourseNumber(const string& token, const string& name) {
    ensuref(token.size() == 4, "%s '%s' must be exactly 4 digits",
            name.c_str(), token.c_str());
    for (char ch : token) {
        ensuref('0' <= ch && ch <= '9', "%s '%s' must contain only digits",
                name.c_str(), token.c_str());
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        string first = inf.readToken("[0-9]+", "k_or_zero");

        if (first == "0") {
            inf.readEoln();
            break;
        }

        ensuref(first.size() == 1 || first[0] != '0',
                "k must not have leading zeros (got '%s')", first.c_str());
        int k = stoi(first);
        ensuref(1 <= k && k <= 100, "k out of range: %d (expected 1..100)", k);

        inf.readSpace();
        int m = inf.readInt(0, 100, "m");
        inf.readEoln();

        vector<string> selected;
        selected.reserve(k);
        while ((int)selected.size() < k) {
            int need = k - (int)selected.size();
            string line = inf.readLine("[^]*", "courses_line"); // match any chars
            vector<string> lineTokens = splitStrictLine(line, "selected course line");
            ensuref((int)lineTokens.size() <= need,
                    "selected course line has too many tokens: got %d, need %d",
                    (int)lineTokens.size(), need);

            for (string &t : lineTokens) {
                ensureCourseNumber(t, "selected course");
                selected.push_back(t);
            }
        }

        {
            set<string> ss(selected.begin(), selected.end());
            ensuref((int)ss.size() == k,
                    "Freddie's selected courses are not distinct (k=%d, unique=%d)",
                    k, (int)ss.size());
        }

        for (int i = 0; i < m; ++i) {
            int c = inf.readInt(1, 100, "c");
            inf.readSpace();
            int r = inf.readInt(0, c, "r");
            vector<string> cat;
            cat.reserve(c);
            for (int j = 0; j < c; ++j) {
                inf.readSpace();
                string t = inf.readToken("[0-9]{4}", "course_in_category");
                cat.push_back(t);
            }
            inf.readEoln();

            set<string> s(cat.begin(), cat.end());
            ensuref((int)s.size() == c,
                    "Category %d has duplicate course numbers (c=%d, unique=%d)",
                    i + 1, c, (int)s.size());
        }
    }

    inf.readEof();
}
