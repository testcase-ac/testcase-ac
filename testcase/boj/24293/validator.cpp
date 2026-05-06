#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Simulate the process to ensure it always ends with exactly 2 characters.
string simulate(string s) {
    bool rev = false;
    while ((int)s.size() > 2) {
        if (rev) {
            reverse(s.begin(), s.end());
        }
        string t;
        t.reserve(s.size());
        int cnt = 0;
        for (char c : s) {
            ++cnt;
            if (cnt % 3 != 0) t.push_back(c);
        }
        s.swap(t);
        rev = !rev; // next step will reverse if size still > 2
    }
    if (rev && (int)s.size() > 1) {
        reverse(s.begin(), s.end());
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the whole line as the string; no extra tokens allowed.
    string s = inf.readLine("[a-z]{1,1000000}", "s");

    // Additional global check: process must end with exactly 2 characters.
    string last = simulate(s);
    ensuref((int)last.size() == 2,
            "Process must end with exactly 2 characters, got %d", (int)last.size());

    inf.readEof();
}
