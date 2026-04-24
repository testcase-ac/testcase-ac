#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int G, L;
vector<string> color; // color[i][j]: 'G' (gray) or 'Y' (yellow)
int SIGMA;

struct Answer {
    bool bugged;
    vector<vector<int>> a; // G rows, L columns: guesses
    vector<int> pass;      // length L: password
};

// Reads an answer (jury or participant). On parsing/format error,
// calls stream.quitf(_wa,...) if stream==ouf, or _fail if stream==ans.
Answer readAns(InStream &stream) {
    Answer res;
    if (stream.seekEof()) {
        stream.quitf(_wa, "unexpected end of output");
    }
    string tok = stream.readWord();
    if (tok == "Bugged!") {
        res.bugged = true;
        return res;
    }
    // Otherwise expect integers: first tok is the first integer
    res.bugged = false;
    int first;
    try {
        size_t pos = 0;
        first = stoi(tok, &pos);
        if (pos != tok.size()) throw 0;
    } catch (...) {
        stream.quitf(_wa, "expected integer or 'Bugged!', found '%s'", tok.c_str());
    }
    // read the G×L matrix of guesses
    res.a.assign(G, vector<int>(L));
    res.a[0][0] = first;
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < L; j++) {
            if (i == 0 && j == 0) continue;
            res.a[i][j] = stream.readInt(-1000000000, 1000000000,
                format("a[%d][%d]", i+1, j+1).c_str());
        }
    }
    // read the password of length L
    res.pass.resize(L);
    for (int j = 0; j < L; j++) {
        res.pass[j] = stream.readInt(-1000000000, 1000000000,
            format("pass[%d]", j+1).c_str());
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    G = inf.readInt();    // number of guesses (called N in statement)
    L = inf.readInt();    // length of each guess (called M in statement)
    color.resize(G);
    for (int i = 0; i < G; i++) {
        color[i] = inf.readToken();
        if ((int)color[i].size() != L)
            inf.quitf(_fail, "bad input: line %d length is %d, expected %d",
                      i+1, (int)color[i].size(), L);
    }
    SIGMA = inf.readInt();

    // Read jury and participant answers
    Answer ansAns = readAns(ans);
    Answer panAns = readAns(ouf);

    // Case: jury says Bugged!
    if (ansAns.bugged) {
        if (panAns.bugged) {
            quitf(_ok, "both say Bugged!");
        } else {
            quitf(_wa, "jury says Bugged! but participant found a solution");
        }
    }
    // jury has a solution
    if (panAns.bugged) {
        quitf(_wa, "participant says Bugged! but a solution exists");
    }

    // Validate participant's solution
    // 1) Dimensions have been read. Check ranges.
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < L; j++) {
            int x = panAns.a[i][j];
            if (x < 1 || x > SIGMA) {
                ouf.quitf(_wa,
                  "guess[%d][%d] = %d is out of range [1..%d]",
                  i+1, j+1, x, SIGMA);
            }
        }
    }
    for (int j = 0; j < L; j++) {
        int x = panAns.pass[j];
        if (x < 1 || x > SIGMA) {
            ouf.quitf(_wa,
              "password[%d] = %d is out of range [1..%d]",
              j+1, x, SIGMA);
        }
    }
    // 2) password must have distinct characters
    {
        vector<int> tmp = panAns.pass;
        sort(tmp.begin(), tmp.end());
        for (int k = 1; k < L; k++) {
            if (tmp[k] == tmp[k-1]) {
                ouf.quitf(_wa,
                  "password has repeated character %d", tmp[k]);
            }
        }
    }
    // 3) check coloring rules and no greens anywhere
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < L; j++) {
            int g = panAns.a[i][j];
            int pw = panAns.pass[j];
            char col = color[i][j];
            // no green allowed
            if (g == pw) {
                ouf.quitf(_wa,
                  "green at guess %d, pos %d: letter %d equals password[%d]",
                  i+1, j+1, g, j+1);
            }
            if (col == 'G') {
                // gray: g must NOT appear anywhere in password
                for (int k = 0; k < L; k++) {
                    if (panAns.pass[k] == g) {
                        ouf.quitf(_wa,
                          "gray at guess %d,pos %d: letter %d appears in password at pos %d",
                          i+1, j+1, g, k+1);
                    }
                }
            } else if (col == 'Y') {
                // yellow: g != pw, and g appears somewhere else in password
                bool found = false;
                for (int k = 0; k < L; k++) {
                    if (k != j && panAns.pass[k] == g) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    ouf.quitf(_wa,
                      "yellow at guess %d,pos %d: letter %d not found elsewhere in password",
                      i+1, j+1, g);
                }
            } else {
                // invalid color in input (shouldn't happen)
                inf.quitf(_fail,
                  "bad input color[%d][%d] = '%c'", i+1, j+1, col);
            }
        }
    }

    // All checks passed
    quitf(_ok, "valid solution");
    return 0;
}
