#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<string> opts = {"pi", "ka", "chu"};
    bool wantValid = rnd.next(0.0, 1.0) < 0.5;
    string s;

    if (wantValid) {
        // Build a valid Pikachu string by concatenating segments until length ≤20
        s.clear();
        while (true) {
            vector<string> cand;
            for (auto &t : opts)
                if ((int)s.size() + (int)t.size() <= 20)
                    cand.push_back(t);
            if (cand.empty()) break;
            // Occasionally stop once we have at least one segment
            if (s.size() >= 2 && rnd.next(0.0, 1.0) < 0.3) break;
            s += rnd.any(cand);
        }
        if (s.empty()) {
            // Fallback to single segment
            s = rnd.any(opts);
        }
    } else {
        // Start from a valid base string (reserve room for junk insertion)
        string base;
        base.clear();
        while (true) {
            vector<string> cand;
            for (auto &t : opts)
                if ((int)base.size() + (int)t.size() <= 19)
                    cand.push_back(t);
            if (cand.empty()) break;
            if (base.size() >= 2 && rnd.next(0.0, 1.0) < 0.3) break;
            base += rnd.any(cand);
        }
        if (base.empty())
            base = rnd.any(opts);
        // Choose a junk char not 'p','k','c' to break segmentation
        string alpha = "abcdefghijklmnopqrstuvwxyz";
        vector<char> others;
        for (char c : alpha)
            if (c != 'p' && c != 'k' && c != 'c')
                others.push_back(c);
        char junk = rnd.any(others);
        int pos = rnd.next(0, (int)base.size());
        s = base.substr(0, pos) + junk + base.substr(pos);
    }

    // Ensure non-empty and within length limit
    if (s.empty()) s = "x";
    if ((int)s.size() > 20) s = s.substr(0, 20);

    // Output the test string
    printf("%s\n", s.c_str());
    return 0;
}
