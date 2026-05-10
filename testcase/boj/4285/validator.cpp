#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We read multiple test cases until a single 0 line appears.
    // Each test:
    // k m
    // one or more lines containing exactly k course numbers (4-digit integers, possibly with leading zeros in token form)
    // then m lines: c r followed by c course numbers.
    // Constraints to validate:
    // 1 ≤ k ≤ 100, 0 ≤ m ≤ 100
    // Each course number token is exactly 4 digits '0'-'9' (string, not numeric).
    // Freddie's k selections are distinct.
    // In each category, the c course numbers are distinct.
    // 1 ≤ c ≤ 100, 0 ≤ r ≤ c
    // Categories can reference courses not selected by Freddie.
    // Global: The line containing 0 is a single token "0" on its own line after previous testcases.

    while (true) {
        // Read first token of a test case: either "0" (end) or k
        string first = inf.readToken("[0-9]+", "k_or_zero");

        if (first == "0") {
            // Must be alone on the line (no extra tokens/spaces except standard spacing rules)
            inf.readEoln();
            break;
        }

        // Canonical integer for k: no leading zeros allowed except "0", but here k >= 1 so disallow all leading zeros.
        ensuref(first.size() == 1 || first[0] != '0',
                "k must not have leading zeros (got '%s')", first.c_str());
        int k = stoi(first);
        ensuref(1 <= k && k <= 100, "k out of range: %d (expected 1..100)", k);

        inf.readSpace();
        int m = inf.readInt(0, 100, "m");
        inf.readEoln();

        // Read k selected courses as tokens across one or more lines.
        // Each token: exactly 4 digits.
        vector<string> selected;
        selected.reserve(k);
        while ((int)selected.size() < k) {
            // Read a full line then split using readTokens via testlib facilities?
            // Simpler: read tokens one by one with regex, separated by spaces, but we must be whitespace-strict.
            // We'll read at most remaining = k - selected.size() tokens from this line.
            int need = k - (int)selected.size();
            // We don't know how many are on this line, so read at least one, then keep using readSpace+peekEoln?
            // But testlib has no peek. Easiest: readLine and then parse manually, but then we circumvent testlib.
            // Alternative standard pattern for UVA-like problems: all k are on a single line.
            // However statement: "One or more lines follow containing k 4-digit integers".
            // We'll emulate line-based reading using readLine and then manual checks consistent with statement.

            // Back up the input pointer isn't possible, so instead,
            // we'll read a full line string and then parse it manually,
            // but still this respects strict EOLs since readLine consumes exactly one line.

            string line = inf.readLine("[^]*", "courses_line"); // match any chars
            // Parse tokens in line manually: separated by spaces.
            stringstream ss(line);
            string tok;
            vector<string> lineTokens;
            while (ss >> tok) lineTokens.push_back(tok);

            ensuref(!lineTokens.empty(),
                    "Line with courses must contain at least one course token");

            for (string &t : lineTokens) {
                ensuref((int)t.size() == 4 &&
                            t[0] >= '0' && t[0] <= '9' &&
                            t[1] >= '0' && t[1] <= '9' &&
                            t[2] >= '0' && t[2] <= '9' &&
                            t[3] >= '0' && t[3] <= '9',
                        "Course number '%s' must be exactly 4 digits", t.c_str());
                selected.push_back(t);
                if ((int)selected.size() == k) break;
            }
        }

        // Check uniqueness of Freddie's selections
        {
            set<string> ss(selected.begin(), selected.end());
            ensuref((int)ss.size() == k,
                    "Freddie's selected courses are not distinct (k=%d, unique=%d)",
                    k, (int)ss.size());
        }

        // Read m categories
        for (int i = 0; i < m; ++i) {
            int c = inf.readInt(1, 100, "c");
            inf.readSpace();
            int r = inf.readInt(0, c, "r");
            // Now read c course numbers
            vector<string> cat;
            cat.reserve(c);
            for (int j = 0; j < c; ++j) {
                inf.readSpace();
                string t = inf.readToken("[0-9]{4}", "course_in_category");
                // Already ensured 4 digits via regex length and digits
                cat.push_back(t);
            }
            inf.readEoln();

            // Ensure category courses are distinct
            set<string> s(cat.begin(), cat.end());
            ensuref((int)s.size() == c,
                    "Category %d has duplicate course numbers (c=%d, unique=%d)",
                    i + 1, c, (int)s.size());
        }
    }

    inf.readEof();
}
