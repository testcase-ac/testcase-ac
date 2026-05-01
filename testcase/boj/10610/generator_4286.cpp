#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Decide if we generate a solvable (multiple of 30) or unsolvable case
    bool solvable = rnd.next(0, 1);
    int L;
    int unsType = -1;
    if (solvable) {
        // To have a zero and non-leading zero, length must be at least 2
        L = rnd.next(2, 10);
    } else {
        // Two kinds of unsolvable: no zero at all, or has zero but sum%3 != 0
        unsType = rnd.next(0, 1);
        if (unsType == 0) {
            // no zero needed, length can be 1..10
            L = rnd.next(1, 10);
        } else {
            // has zero but sum%3 != 0, length at least 2
            L = rnd.next(2, 10);
        }
    }

    string s;
    s.reserve(L);

    if (solvable) {
        // Build a string with at least one zero (not leading) and sum of digits %3 == 0
        while (true) {
            s.assign(L, '0');
            // First digit non-zero
            s[0] = char('0' + rnd.next(1, 9));
            // Place at least one zero in positions [1..L-1]
            int zp = rnd.next(1, L - 1);
            s[zp] = '0';
            // Fill other positions with random digits 0-9
            for (int i = 1; i < L; i++) {
                if (i == zp) continue;
                s[i] = char('0' + rnd.next(0, 9));
            }
            // Check divisibility by 3
            int sum = 0;
            for (char c : s) sum += c - '0';
            if (sum % 3 == 0) break;
        }
    } else {
        if (unsType == 0) {
            // No zero at all
            s.assign(L, '0');
            s[0] = char('0' + rnd.next(1, 9));
            for (int i = 1; i < L; i++) {
                s[i] = char('0' + rnd.next(1, 9));
            }
        } else {
            // Has at least one zero (not leading), but sum%3 != 0
            while (true) {
                s.assign(L, '0');
                // First digit non-zero
                s[0] = char('0' + rnd.next(1, 9));
                // Place one zero at a non-leading position
                int zp = rnd.next(1, L - 1);
                s[zp] = '0';
                // Fill others randomly
                for (int i = 1; i < L; i++) {
                    if (i == zp) continue;
                    s[i] = char('0' + rnd.next(0, 9));
                }
                int sum = 0;
                for (char c : s) sum += c - '0';
                if (sum % 3 != 0) break;
            }
        }
    }

    // Output the generated number
    printf("%s\n", s.c_str());
    return 0;
}
