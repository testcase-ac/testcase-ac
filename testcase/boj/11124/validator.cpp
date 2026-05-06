#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    // Problem explicitly: 0 < T ≤ 100
    ensuref(T <= 100, "T must be at most 100, got %d", T);
    inf.readEoln();

    auto isColor = [](char c) {
        return c=='G' || c=='R' || c=='O' || c=='B' || c=='Y' || c=='W';
    };

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        vector<char> stickers;
        stickers.reserve(24);

        // Line 1: exactly 2 chars, no spaces
        {
            string s = inf.readToken("[A-Z]{2}", "line1");
            inf.readEoln();
            ensuref((int)s.size() == 2, "Test %d: line1 must have length 2", tc+1);
            for (char c : s) {
                ensuref(isColor(c), "Test %d: invalid color '%c' in line1", tc+1, c);
                stickers.push_back(c);
            }
        }

        // Line 2: exactly 2 chars, no spaces
        {
            string s = inf.readToken("[A-Z]{2}", "line2");
            inf.readEoln();
            ensuref((int)s.size() == 2, "Test %d: line2 must have length 2", tc+1);
            for (char c : s) {
                ensuref(isColor(c), "Test %d: invalid color '%c' in line2", tc+1, c);
                stickers.push_back(c);
            }
        }

        // Helper to read a "AA BB CC DD" line strictly
        auto readMiddleLine = [&](const char* name) {
            // Four blocks of exactly two letters, single spaces between, no leading/trailing spaces
            string line = inf.readLine("[A-Z]{2}\\ [A-Z]{2}\\ [A-Z]{2}\\ [A-Z]{2}", name);
            vector<string> parts;
            string cur;
            for (char ch : line) {
                if (ch == ' ') {
                    if (!cur.empty()) {
                        parts.push_back(cur);
                        cur.clear();
                    }
                } else {
                    cur.push_back(ch);
                }
            }
            if (!cur.empty()) parts.push_back(cur);
            return parts;
        };

        // Line 3: "AA BB CC DD"
        {
            vector<string> parts = readMiddleLine("line3");
            ensuref(parts.size() == 4, "Test %d: line3 must contain 4 blocks", tc+1);
            for (int k = 0; k < 4; ++k) {
                ensuref(parts[k].size() == 2, "Test %d: block %d in line3 must have length 2", tc+1, k+1);
                for (char c : parts[k]) {
                    ensuref(isColor(c), "Test %d: invalid color '%c' in line3", tc+1, c);
                    stickers.push_back(c);
                }
            }
        }

        // Line 4: "AA BB CC DD"
        {
            vector<string> parts = readMiddleLine("line4");
            ensuref(parts.size() == 4, "Test %d: line4 must contain 4 blocks", tc+1);
            for (int k = 0; k < 4; ++k) {
                ensuref(parts[k].size() == 2, "Test %d: block %d in line4 must have length 2", tc+1, k+1);
                for (char c : parts[k]) {
                    ensuref(isColor(c), "Test %d: invalid color '%c' in line4", tc+1, c);
                    stickers.push_back(c);
                }
            }
        }

        // Line 5: exactly 2 chars, no spaces
        {
            string s = inf.readToken("[A-Z]{2}", "line5");
            inf.readEoln();
            ensuref((int)s.size() == 2, "Test %d: line5 must have length 2", tc+1);
            for (char c : s) {
                ensuref(isColor(c), "Test %d: invalid color '%c' in line5", tc+1, c);
                stickers.push_back(c);
            }
        }

        // Line 6: exactly 2 chars, no spaces
        {
            string s = inf.readToken("[A-Z]{2}", "line6");
            inf.readEoln();
            ensuref((int)s.size() == 2, "Test %d: line6 must have length 2", tc+1);
            for (char c : s) {
                ensuref(isColor(c), "Test %d: invalid color '%c' in line6", tc+1, c);
                stickers.push_back(c);
            }
        }

        // After each test case, there is an empty line.
        // The last test case may or may not be followed by a truly empty line
        // depending on how the input is formatted, but statement says it is,
        // so we enforce it when possible.
        if (tc + 1 < T) {
            // Must be exactly empty
            string emp = inf.readLine("[^]*", "empty_line");
            ensuref(emp.empty(), "Test %d: expected an empty line after test case", tc+1);
        } else {
            // Last test: attempt to read an empty line only if there is still data
            if (!inf.eof()) {
                string emp = inf.readLine("[^]*", "empty_line_last");
                ensuref(emp.empty(), "Test %d: expected an empty line after last test case", tc+1);
            }
        }

        // Sanity: total 24 stickers
        ensuref((int)stickers.size() == 24,
                "Test %d: total stickers should be 24, got %d",
                tc+1, (int)stickers.size());

        // Color multiset constraint: exactly 6 distinct colors, each 4 times
        map<char,int> cnt;
        for (char c : stickers) cnt[c]++;
        ensuref((int)cnt.size() == 6,
                "Test %d: there must be exactly 6 distinct colors, got %d",
                tc+1, (int)cnt.size());
        for (auto &p : cnt) {
            ensuref(p.second == 4,
                    "Test %d: color '%c' must appear exactly 4 times, got %d",
                    tc+1, p.first, p.second);
        }
    }

    inf.readEof();
}
