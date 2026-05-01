#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: k biased towards larger values but still 1..8
    int k = rnd.wnext(8, 2) + 1;

    // Decide how many D vs U for the k horizontal folds
    int dCount = rnd.next(0, k);
    int uCount = k - dCount;
    vector<char> hlist;
    for (int i = 0; i < dCount; i++) hlist.push_back('D');
    for (int i = 0; i < uCount; i++) hlist.push_back('U');

    // Decide how many R vs L for the k vertical folds
    int rCount = rnd.next(0, k);
    int lCount = k - rCount;
    vector<char> vlist;
    for (int i = 0; i < rCount; i++) vlist.push_back('R');
    for (int i = 0; i < lCount; i++) vlist.push_back('L');

    // Hyper-parameter: pattern of mixing horizontals and verticals
    // 0 = fully random shuffle, 1 = grouped (H then V), 2 = alternating as much as possible
    int pattern = rnd.next(0, 2);
    vector<char> seq;
    if (pattern == 0) {
        seq = hlist;
        seq.insert(seq.end(), vlist.begin(), vlist.end());
        shuffle(seq.begin(), seq.end());
    } else if (pattern == 1) {
        // grouped: all horizontals then all verticals
        seq = hlist;
        seq.insert(seq.end(), vlist.begin(), vlist.end());
    } else {
        // alternating H and V
        int hi = 0, vi = 0, total = 2 * k;
        for (int i = 0; i < total; i++) {
            if ((i % 2 == 0 && hi < (int)hlist.size()) || vi == (int)vlist.size()) {
                seq.push_back(hlist[hi++]);
            } else {
                seq.push_back(vlist[vi++]);
            }
        }
    }

    // Hole position
    int hpos = rnd.next(0, 3);

    // Output
    println(k);
    for (int i = 0; i < (int)seq.size(); i++) {
        printf("%c%c", seq[i], (i + 1 == (int)seq.size() ? '\n' : ' '));
    }
    println(hpos);

    return 0;
}
