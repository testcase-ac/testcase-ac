#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read jury answers into a vector
    vector<string> jury;
    while (!ans.seekEof()) {
        string t = ans.readToken();
        jury.push_back(t);
    }
    // Read contestant answers into a vector
    vector<string> user;
    while (!ouf.seekEof()) {
        // If contestant prints nothing, that's a PE/WA
        if (ouf.eof()) break;
        string t = ouf.readToken();
        user.push_back(t);
    }
    // It must not be empty
    if (user.empty()) {
        quitf(_wa, "no output");
    }
    // Check for duplicates in jury (shouldn't happen)
    {
        set<string> sj(jury.begin(), jury.end());
        if ((int)sj.size() != (int)jury.size()) {
            quitf(_fail, "internal error: duplicates in jury output");
        }
    }
    // Check for duplicates in user output
    {
        set<string> su(user.begin(), user.end());
        if ((int)su.size() != (int)user.size()) {
            quitf(_wa, "duplicate strings in output");
        }
    }
    // Compare sets
    set<string> sj(jury.begin(), jury.end());
    set<string> su(user.begin(), user.end());
    if (sj != su) {
        // find missing and unexpected
        for (auto &s : sj) {
            if (!su.count(s)) {
                quitf(_wa, "missing expected string: \"%s\"", s.c_str());
            }
        }
        for (auto &s : su) {
            if (!sj.count(s)) {
                quitf(_wa, "unexpected string in output: \"%s\"", s.c_str());
            }
        }
        // should never reach here
        quitf(_wa, "output mismatch");
    }
    quitf(_ok, "correct");
}
