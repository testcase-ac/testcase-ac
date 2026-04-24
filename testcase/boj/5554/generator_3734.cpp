#include "testlib.h"
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total time in seconds between 1:00 and 59:59 inclusive
    int T = rnd.next(60, 3599);
    vector<int> parts(4);

    // Choose a style for partitioning T into 4 positive integers
    int style = rnd.next(0, 2);

    if (style == 0) {
        // style 0: uniform random partition via 3 distinct breakpoints
        set<int> used;
        vector<int> cuts = {0, T};
        while ((int)used.size() < 3) {
            int x = rnd.next(1, T - 1);
            if (used.insert(x).second) {
                cuts.push_back(x);
            }
        }
        sort(cuts.begin(), cuts.end());
        for (int i = 0; i < 4; i++) {
            parts[i] = cuts[i+1] - cuts[i];
        }
    }
    else if (style == 1) {
        // style 1: one large segment, three small segments
        int bigIdx = rnd.next(0, 3);
        // big segment at least half of T but leave at least 3 seconds
        int big = rnd.next(T/2, T - 3);
        parts[bigIdx] = big;
        int rem = T - big;
        // partition rem into 3 positive parts
        set<int> used;
        vector<int> cuts = {0, rem};
        while ((int)used.size() < 2) {
            int x = rnd.next(1, rem - 1);
            if (used.insert(x).second) {
                cuts.push_back(x);
            }
        }
        sort(cuts.begin(), cuts.end());
        vector<int> small(3);
        for (int i = 0; i < 3; i++) {
            small[i] = cuts[i+1] - cuts[i];
        }
        // fill the other positions
        for (int i = 0, j = 0; i < 4; i++) {
            if (i == bigIdx) continue;
            parts[i] = small[j++];
        }
    }
    else {
        // style 2: roughly balanced, distribute remainder
        int base = T / 4;
        int rem = T - base * 4;
        for (int i = 0; i < 4; i++) {
            parts[i] = base + (i < rem ? 1 : 0);
        }
        shuffle(parts.begin(), parts.end());
    }

    // Output four lines
    for (int i = 0; i < 4; i++) {
        println(parts[i]);
    }
    return 0;
}
