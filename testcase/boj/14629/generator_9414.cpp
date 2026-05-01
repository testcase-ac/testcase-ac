#include "testlib.h"
using namespace std;

long long genConstructible() {
    // Generate a number using distinct digits 0..9, no leading zero
    int len = rnd.next(1, 10);

    vector<int> avail;
    for (int d = 0; d <= 9; ++d) avail.push_back(d);

    vector<int> digits;
    // choose first digit from 1..9 (no leading zero)
    int idxFirst = rnd.next(1, 9); // avail is {0,1,2,...,9}, so indices 1..9 map to digits 1..9
    int firstDigit = avail[idxFirst];
    digits.push_back(firstDigit);
    avail.erase(avail.begin() + idxFirst);

    // choose remaining distinct digits
    for (int i = 1; i < len; ++i) {
        int idx = rnd.next(0, (int)avail.size() - 1);
        digits.push_back(avail[idx]);
        avail.erase(avail.begin() + idx);
    }

    long long val = 0;
    for (int d : digits) val = val * 10 + d;
    return val;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long N = 1;

    int type = rnd.next(1, 7);

    if (type == 1) {
        // Very small numbers and patterned small values
        vector<long long> smalls = {
            1,2,3,4,5,6,7,8,9,
            10,11,12,13,19,20,21,25,29,
            30,31,32,33,34,39,
            44,55,66,77,88,99,
            100,101,110,111,123,321
        };
        if (rnd.next(0, 1) == 0) {
            N = rnd.any(smalls);
        } else {
            N = rnd.next(1LL, 1000LL);
        }
    } else if (type == 2) {
        // Around the maximum constructible number 9876543210
        long long maxCand = 9876543210LL;
        vector<long long> around = {
            maxCand,
            maxCand - 1,
            maxCand - 2,
            maxCand - 10,
            maxCand - 100,
            maxCand + 1,
            maxCand + 2,
            maxCand + 10,
            maxCand + 100,
            maxCand / 2
        };
        N = rnd.any(around);
    } else if (type == 3) {
        // Fully random in the whole allowed range
        N = rnd.next(1LL, 1000000000000LL); // [1, 1e12]
    } else if (type == 4) {
        // Near boundaries of the allowed range
        if (rnd.next(0, 1) == 0) {
            // Near 1
            long long lo = 1, hi = 1000;
            N = rnd.next(lo, hi);
        } else {
            // Near 1e12
            long long hi = 1000000000000LL;
            long long lo = hi - 1000;
            N = rnd.next(lo, hi);
        }
    } else if (type == 5) {
        // N equals a random valid constructible number
        N = genConstructible();
    } else if (type == 6) {
        // N near a constructible number
        long long base = genConstructible();
        long long delta = rnd.next(1, 1000);
        if (base <= delta || rnd.next(0, 1) == 0) {
            N = base + delta;
        } else {
            N = base - delta;
        }
        if (N < 1) N = 1;
        if (N > 1000000000000LL) N = 1000000000000LL;
    } else if (type == 7) {
        // Guaranteed tie-cases: N exactly between two optimal constructible numbers
        // Examples:
        // N = 22 -> candidates 21 and 23 (both valid, 22 invalid due to repeated digit)
        vector<long long> ties = {22, 33, 44, 55, 66, 77, 88};
        N = rnd.any(ties);
    }

    println(N);
    return 0;
}
