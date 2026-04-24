#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // length of the number (2 to 9 digits to ensure <= 2147483647)
    int L = rnd.next(2, 9);
    // decide if we want a YES or NO case
    bool wantYES = rnd.next(0, 1) == 1;
    vector<int> digits;
    if (wantYES) {
        // generate a "YES" (유진수) case
        double zeroProb = rnd.next(0.0, 1.0);
        if (L >= 3 && rnd.next() < zeroProb) {
            // ZERO-PRODUCT type: both sides have at least one zero => products = 0
            int p = rnd.next(2, L - 1);  // split point, left length p >= 2
            int zeroPosL = rnd.next(1, p - 1);
            int zeroPosR = rnd.next(p, L - 1);
            digits.assign(L, 0);
            // fill left part
            for (int i = 0; i < p; i++) {
                if (i == zeroPosL) digits[i] = 0;
                else digits[i] = rnd.next(1, 9);
            }
            // fill right part
            for (int i = p; i < L; i++) {
                if (i == zeroPosR) digits[i] = 0;
                else digits[i] = rnd.next(1, 9);
            }
        } else {
            // NON-ZERO-PRODUCT type: pick left block, copy to right and pad with 1s
            int p = rnd.next(1, L / 2);
            vector<int> left(p);
            for (int i = 0; i < p; i++)
                left[i] = rnd.next(1, 9);
            // shuffle left for diversity
            shuffle(left.begin(), left.end());
            // build right block: start with same digits, then pad 1s
            vector<int> right = left;
            right.resize(L - p, 1);
            shuffle(right.begin(), right.end());
            digits.assign(L, 1);
            for (int i = 0; i < p; i++) digits[i] = left[i];
            for (int i = p; i < L; i++) digits[i] = right[i - p];
        }
    } else {
        // generate a "NO" (비유진수) case
        // brute-force random until no split yields equal-products
        while (true) {
            digits.resize(L);
            // first digit non-zero
            digits[0] = rnd.next(1, 9);
            for (int i = 1; i < L; i++)
                digits[i] = rnd.next(0, 9);
            bool hasEug = false;
            for (int p = 1; p < L; p++) {
                long long prodL = 1, prodR = 1;
                for (int i = 0; i < p; i++) prodL *= digits[i];
                for (int i = p; i < L; i++) prodR *= digits[i];
                if (prodL == prodR) {
                    hasEug = true;
                    break;
                }
            }
            if (!hasEug) break;
        }
    }
    // output the number
    string s;
    s.reserve(L);
    for (int d : digits) s.push_back(char('0' + d));
    println(s);
    return 0;
}
