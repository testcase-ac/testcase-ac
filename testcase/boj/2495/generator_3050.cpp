#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> t_values = {-2, -1, 0, 1, 2};
    for (int rep = 0; rep < 3; rep++) {
        int t = rnd.any(t_values);
        int runs = rnd.wnext(8, t) + 1;  // between 1 and 8 blocks

        // partition length 8 into 'runs' positive parts
        vector<int> lengths;
        if (runs == 1) {
            lengths.push_back(8);
        } else {
            vector<int> cuts(7);
            for (int i = 0; i < 7; i++) cuts[i] = i + 1;
            shuffle(cuts.begin(), cuts.end());
            vector<int> sel(cuts.begin(), cuts.begin() + (runs - 1));
            sel.push_back(0);
            sel.push_back(8);
            sort(sel.begin(), sel.end());
            for (int i = 1; i < (int)sel.size(); i++) {
                lengths.push_back(sel[i] - sel[i - 1]);
            }
        }

        // build the 8-digit string with no two adjacent blocks having same digit
        string s;
        s.reserve(8);
        int prev = -1;
        for (int len : lengths) {
            int d;
            if (prev == -1) {
                d = rnd.next(1, 9);
            } else {
                do {
                    d = rnd.next(0, 9);
                } while (d == prev);
            }
            prev = d;
            s += string(len, char('0' + d));
        }

        printf("%s\n", s.c_str());
    }
    return 0;
}
