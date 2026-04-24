#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> species;
    species.reserve(1000);

    // Read all species names, one per line, until EOF
    int line_no = 1;
    while (!inf.eof()) {
        // Read a line: any characters except end-of-line (including spaces)
        string s = inf.readLine("[^]+", "species");
        int len = s.size();
        // Each name must be non-empty and at most 30 characters
        ensuref(len >= 1 && len <= 30,
                "Line %d: species name length must be between 1 and 30, got %d",
                line_no, len);
        species.push_back(s);
        line_no++;
    }

    // Total number of trees (lines) must be between 1 and 1e6
    int64_t total = species.size();
    ensuref(total >= 1 && total <= 1000000,
            "Total number of trees must be between 1 and 1000000, got %lld",
            (long long)total);

    // Distinct species must be at most 10000
    vector<string> tmp = species;
    sort(tmp.begin(), tmp.end());
    int distinct = int(unique(tmp.begin(), tmp.end()) - tmp.begin());
    ensuref(distinct <= 10000,
            "Number of distinct species must be at most 10000, got %d",
            distinct);

    inf.readEof();
    return 0;
}
