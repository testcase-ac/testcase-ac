#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of gears T: biased towards larger but within [1,15]
    int T = rnd.wnext(15, 3) + 1;

    // Generate gear states with diverse patterns
    vector<string> gears;
    for (int i = 0; i < T; i++) {
        int pat = rnd.next(0, 5);
        string s(8, '0');
        switch (pat) {
            case 0: // random bits
                for (int j = 0; j < 8; j++)
                    s[j] = char('0' + rnd.next(0,1));
                break;
            case 1: // all N (0)
                // already zeros
                break;
            case 2: // all S (1)
                for (int j = 0; j < 8; j++) s[j] = '1';
                break;
            case 3: // alternating 0,1 starting 0
                for (int j = 0; j < 8; j++) s[j] = char('0' + (j % 2));
                break;
            case 4: // alternating 0,1 starting 1
                for (int j = 0; j < 8; j++) s[j] = char('0' + ((j+1) % 2));
                break;
            case 5: // half zeros then half ones, maybe reversed
                if (rnd.next(0,1) == 0) {
                    for (int j = 0; j < 4; j++) s[j] = '0';
                    for (int j = 4; j < 8; j++) s[j] = '1';
                } else {
                    for (int j = 0; j < 4; j++) s[j] = '1';
                    for (int j = 4; j < 8; j++) s[j] = '0';
                }
                break;
        }
        gears.push_back(s);
    }

    // Number of rotations K: biased towards small but up to 20
    int K = rnd.wnext(20, -1) + 1;

    // Operation sequence hyper-parameters
    int seqType = rnd.next(0, 2);
    int dirType = rnd.next(0, 2);

    vector<pair<int,int>> ops;
    ops.reserve(K);

    // Prepare zigzag pointers if needed
    int l = 1, r = T;
    bool pickL = true;

    // Global direction if dirType==1
    int globalD = (rnd.next(0,1) == 0 ? -1 : 1);

    for (int i = 0; i < K; i++) {
        int idx;
        if (seqType == 0) {
            // random gear
            idx = rnd.next(1, T);
        } else if (seqType == 1) {
            // cycling 1..T
            idx = (i % T) + 1;
        } else {
            // zigzag 1, T, 2, T-1, ...
            idx = pickL ? l++ : r--;
            if (l > r) { l = 1; r = T; } // reset if exhausted
            pickL = !pickL;
        }
        int d;
        if (dirType == 0) {
            // random direction each
            d = rnd.next(0,1) == 0 ? -1 : 1;
        } else if (dirType == 1) {
            // same direction
            d = globalD;
        } else {
            // alternating directions
            d = (i % 2 == 0 ? 1 : -1);
        }
        ops.emplace_back(idx, d);
    }

    // Output
    println(T);
    for (auto &s : gears) println(s);
    println(K);
    for (auto &op : ops) println(op.first, op.second);

    return 0;
}
