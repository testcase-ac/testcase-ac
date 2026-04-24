#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Category: 0->unrelated, 1->related but not close, 2->close but not tied, 3->tied
    int cat = rnd.next(0, 3);
    string s;
    if (cat == 0) {
        // Unrelated: must contain at least one forbidden digit (not in {2,0,1,8})
        int L = rnd.next(1, 9);
        vector<char> digs(L);
        int pos = rnd.next(0, L - 1);
        string forb = "345679";  // forbidden digits
        for (int i = 0; i < L; i++) {
            if (i == pos) {
                digs[i] = rnd.any(forb);
            } else {
                if (i == 0) {
                    // no leading zero
                    int d = rnd.next(1, 9);
                    digs[i] = char('0' + d);
                } else {
                    int d = rnd.next(0, 9);
                    digs[i] = char('0' + d);
                }
            }
        }
        s.assign(digs.begin(), digs.end());
    } else if (cat == 1) {
        // Related but missing at least one of {2,0,1,8}
        int mask = rnd.next(1, 7);  // subset of {1,2,8}
        vector<char> sub;
        if (mask & 1) sub.push_back('1');
        if (mask & 2) sub.push_back('2');
        if (mask & 4) sub.push_back('8');
        // optionally include zero if not all three present
        if (mask != 7 && rnd.next(0, 1) == 1) sub.push_back('0');
        int L = rnd.next(1, 9);
        vector<char> digs(L);
        for (int i = 0; i < L; i++) {
            if (i == 0) {
                // ensure no leading zero
                vector<char> non0;
                for (char c : sub) if (c != '0') non0.push_back(c);
                digs[i] = rnd.any(non0);
            } else {
                digs[i] = rnd.any(sub);
            }
        }
        s.assign(digs.begin(), digs.end());
    } else if (cat == 2) {
        // Close but counts of {2,0,1,8} are not all equal
        int extra = rnd.next(1, 3); // add between 1 and 3 extra occurrences
        vector<int> cnt(4, 1); // initial one of each
        for (int i = 0; i < extra; i++) {
            int j = rnd.next(0, 3);
            cnt[j]++;
        }
        string digits = "2018";
        vector<char> digs;
        for (int j = 0; j < 4; j++)
            for (int t = 0; t < cnt[j]; t++)
                digs.push_back(digits[j]);
        shuffle(digs.begin(), digs.end());
        // fix leading zero if happens
        if (!digs.empty() && digs[0] == '0') {
            for (int i = 1; i < (int)digs.size(); i++) {
                if (digs[i] != '0') {
                    swap(digs[0], digs[i]);
                    break;
                }
            }
        }
        s.assign(digs.begin(), digs.end());
    } else {
        // Tied: equal counts of each digit, up to total length 8
        int k = rnd.next(1, 2); // 4*k <= 8
        string digits = "2018";
        vector<char> digs;
        for (int j = 0; j < 4; j++)
            for (int t = 0; t < k; t++)
                digs.push_back(digits[j]);
        shuffle(digs.begin(), digs.end());
        if (!digs.empty() && digs[0] == '0') {
            for (int i = 1; i < (int)digs.size(); i++) {
                if (digs[i] != '0') {
                    swap(digs[0], digs[i]);
                    break;
                }
            }
        }
        s.assign(digs.begin(), digs.end());
    }
    // Output the generated number
    println(s);
    return 0;
}
