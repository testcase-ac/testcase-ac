#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 99, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        string line = inf.readLine();
        ensuref(!line.empty(), "testcase %d line is empty", tc);
        ensuref(line.front() != ' ' && line.back() != ' ',
                "testcase %d has leading or trailing space", tc);
        ensuref(line.find("  ") == string::npos,
                "testcase %d has repeated spaces", tc);

        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        int M = (int)tokens.size();
        ensuref(M >= 2 && M <= 99,
                "testcase %d has %d integers, expected [2,99]", tc, M);

        for (int i = 0; i < M; ++i) {
            const string& s = tokens[i];
            ensuref(s[0] >= '1' && s[0] <= '9',
                    "testcase %d token %d is not a positive canonical integer",
                    tc, i + 1);
            long long val = 0;
            for (char c : s) {
                ensuref(c >= '0' && c <= '9',
                        "testcase %d token %d contains a non-digit character",
                        tc, i + 1);
                val = val * 10 + (c - '0');
                ensuref(val <= 2147483647LL,
                        "testcase %d token %d is greater than 2^31 - 1",
                        tc, i + 1);
            }
        }
    }

    inf.readEof();
    return 0;
}
