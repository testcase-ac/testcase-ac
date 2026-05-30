#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> species;
    species.reserve(10000);

    int line_no = 1;
    while (!inf.eof()) {
        string s = inf.readLine();

        int len = int(s.size());
        ensuref(1 <= len && len <= 30,
                "Line %d: species name length must be between 1 and 30, got %d",
                line_no, len);

        bool has_non_space = false;
        for (unsigned char ch : s) {
            ensuref(32 <= ch && ch <= 126,
                    "Line %d: invalid character code %u", line_no, ch);
            if (ch != ' ') {
                has_non_space = true;
            }
        }
        ensuref(has_non_space, "Line %d: species name must not be whitespace-only", line_no);

        species.push_back(s);
        line_no++;
    }

    int64_t total = species.size();
    ensuref(total >= 1 && total <= 1000000,
            "Total number of trees must be between 1 and 1000000, got %lld",
            (long long)total);

    vector<string> tmp = species;
    sort(tmp.begin(), tmp.end());
    int distinct = int(unique(tmp.begin(), tmp.end()) - tmp.begin());
    ensuref(distinct <= 10000,
            "Number of distinct species must be at most 10000, got %d",
            distinct);

    inf.readEof();
    return 0;
}
