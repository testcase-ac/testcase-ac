#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem statement describes a single test case:
    // "The input consists of seven digits of the NICE."
    // So we read exactly one token of 7 digits, no extra spaces, then EOF.

    string s = inf.readToken("[0-9]{7}", "nice_digits");
    inf.readEoln();

    // Additionally, we verify the implied checksum mapping described
    // in the statement by actually computing the letter.
    // This ensures that any provided full NICE number (if used by
    // generators) matches the described behavior, but here we only have digits.
    // There is no further global constraint to check (answer always exists).

    // Still, to follow instructions about global properties:
    // verify that mapping for any 7-digit string is always defined.
    // The remainder is always in [0,10], and mapping array covers it.

    int w[7] = {2,7,6,5,4,3,2};
    long long sum = 0;
    for (int i = 0; i < 7; ++i) {
        int d = s[i] - '0';
        sum += 1LL * d * w[i];
    }
    int r = int(sum % 11);
    ensuref(0 <= r && r <= 10, "Remainder out of range: %d", r);

    const char mp[11] = {'J','A','B','C','D','E','F','G','H','I','Z'};
    char ch = mp[r];
    ensuref(ch >= 'A' && ch <= 'Z', "Mapped character not uppercase: %c", ch);

    inf.readEof();
}
