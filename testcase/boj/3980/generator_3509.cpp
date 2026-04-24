#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int C = 1;
    println(C);
    for (int tc = 0; tc < C; tc++) {
        // Create a guaranteed perfect matching
        vector<int> perm(11);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        vector<vector<int>> s(11, vector<int>(11, 0));
        for (int i = 0; i < 11; i++) {
            int matched = perm[i] - 1;
            // Decide number of valid positions for player i
            int k;
            if (rnd.next() < 0.5) {
                k = rnd.next(1, 3);
            } else {
                k = rnd.next(2, 5);
            }
            // Always include the matched position
            vector<int> avail;
            for (int j = 0; j < 11; j++) if (j != matched) avail.push_back(j);
            shuffle(avail.begin(), avail.end());
            vector<int> pos;
            pos.push_back(matched);
            for (int t = 0; t < k-1 && t < (int)avail.size(); t++) {
                pos.push_back(avail[t]);
            }
            // Assign abilities
            for (int j : pos) {
                if (j == matched) {
                    s[i][j] = rnd.next(50, 100);
                } else {
                    s[i][j] = rnd.next(1, 49);
                }
            }
        }
        // Output this test case
        for (int i = 0; i < 11; i++) {
            println(s[i]);
        }
    }
    return 0;
}
