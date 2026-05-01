#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose even length n between 2 and 30
    int n = 2 * rnd.next(1, 15);
    // Choose number of zeros Z (even) and ones O = n - Z
    int Z2 = rnd.next(0, n / 2);
    int Z = 2 * Z2;
    int O = n - Z;

    vector<char> s;
    // Edge cases: all zeros or all ones
    if (Z == 0) {
        s.assign(O, '1');
    } else if (O == 0) {
        s.assign(Z, '0');
    } else {
        int type = rnd.next(0, 2);
        if (type == 0) {
            // Uniform random shuffle
            s.reserve(n);
            for (int i = 0; i < Z; i++) s.push_back('0');
            for (int i = 0; i < O; i++) s.push_back('1');
            shuffle(s.begin(), s.end());
        } else if (type == 1) {
            // Few alternating blocks
            int maxBlocks = min(2 * min(Z, O), 6);
            int blocks = rnd.next(2, maxBlocks);
            int neededPerStart = (blocks + 1) / 2;
            vector<char> starts;
            if (Z >= neededPerStart) starts.push_back('0');
            if (O >= neededPerStart) starts.push_back('1');
            char start = rnd.any(starts);
            int blk0 = (start == '0' ? (blocks + 1) / 2 : blocks / 2);
            int blk1 = blocks - blk0;
            // Initialize lengths with 1 each
            vector<int> len0(blk0, 1), len1(blk1, 1);
            int rem0 = Z - blk0;
            for (int i = 0; i < rem0; i++) {
                int idx = rnd.next(0, blk0 - 1);
                len0[idx]++;
            }
            int rem1 = O - blk1;
            for (int i = 0; i < rem1; i++) {
                int idx = rnd.next(0, blk1 - 1);
                len1[idx]++;
            }
            // Build the string
            s.reserve(n);
            int i0 = 0, i1 = 0;
            char cur = start;
            for (int b = 0; b < blocks; b++) {
                if (cur == '0') {
                    for (int k = 0; k < len0[i0]; k++) s.push_back('0');
                    i0++;
                } else {
                    for (int k = 0; k < len1[i1]; k++) s.push_back('1');
                    i1++;
                }
                cur = (cur == '0' ? '1' : '0');
            }
        } else {
            // Monotonic: zeros then ones or ones then zeros
            bool zeroFirst = rnd.next(0, 1) == 0;
            if (zeroFirst) {
                s.assign(Z, '0');
                for (int i = 0; i < O; i++) s.push_back('1');
            } else {
                s.assign(O, '1');
                for (int i = 0; i < Z; i++) s.push_back('0');
            }
        }
    }

    // Output the generated string
    printf("%s\n", string(s.begin(), s.end()).c_str());
    return 0;
}
