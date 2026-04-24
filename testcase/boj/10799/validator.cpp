#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line of parentheses: '(' and ')' only
    // Length up to 100000; we enforce minimum length via ensuref below
    string s = inf.readLine("[()]{1,100000}", "s");
    int L = (int)s.size();
    ensuref(L >= 2, "Input length must be at least 2, got %d", L);
    ensuref(L <= 100000, "Input length must be at most 100000, got %d", L);
    ensuref(L % 2 == 0, "Input length must be even, got %d", L);

    // We classify each "()" as a laser; all other '(' and ')' form rods.
    vector<int> bar_stack;            // stack of positions of '(' that start rods
    vector<pair<int,int>> bars;       // intervals [open, close] of each rod
    vector<int> lasers;               // positions of laser start '('

    for (int i = 0; i < L; i++) {
        char c = s[i];
        if (c == '(') {
            // Potential laser if next char is ')'
            if (i + 1 < L && s[i+1] == ')') {
                // Laser detected at positions i ('(') and i+1 (')')
                lasers.push_back(i);
                i++; // skip the ')'
            } else {
                // Start of a rod
                bar_stack.push_back(i);
            }
        } else {
            // c == ')'
            // This must close a rod, not be part of a laser (we skip lasers above)
            ensuref(!bar_stack.empty(),
                    "Unmatched closing parenthesis ')' at position %d", i);
            int open_pos = bar_stack.back();
            bar_stack.pop_back();
            bars.emplace_back(open_pos, i);
        }
    }
    // No unmatched '(' should remain
    ensuref(bar_stack.empty(),
            "Unmatched opening parenthesis '(' at position %d",
            bar_stack.empty() ? -1 : bar_stack.back());

    // Each rod must have at least one laser strictly inside its interval
    sort(lasers.begin(), lasers.end());
    for (int idx = 0; idx < (int)bars.size(); idx++) {
        int l = bars[idx].first;
        int r = bars[idx].second;
        // We need a laser start p with l < p and p+1 < r  =>  p in [l+1, r-2]
        auto it = lower_bound(lasers.begin(), lasers.end(), l+1);
        bool found = false;
        if (it != lasers.end() && *it + 1 < r) {
            found = true;
        }
        ensuref(found,
                "Rod #%d spanning positions [%d, %d] has no laser strictly inside",
                idx, l, r);
    }

    // No extra input
    inf.readEof();
    return 0;
}
