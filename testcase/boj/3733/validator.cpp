#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input consists of pairs of integers N and S, separated by arbitrary whitespace,
    // and terminated by EOF. Each pair must satisfy:
    // 1 <= N <= 10000
    // 1 <= S <= 10^9

    // The input is "correct", so we do not need to check for malformed input,
    // but we must check the constraints and that there are no extra tokens after EOF.

    // Since input is whitespace-separated, we read tokens until EOF.
    // Each pair of tokens is N and S.

    int pairCount = 0;
    while (!inf.seekEof()) {
        // Read N
        int N = inf.readInt(1, 10000, "N");
        // After N, there may be whitespace (space, tab, newline)
        if (inf.seekEof()) {
            ensuref(false, "Unexpected EOF after N at pair index %d", pairCount + 1);
        }
        // Read S
        int S = inf.readInt(1, 1000000000, "S");
        ++pairCount;
        // After S, there may be whitespace or EOF
        // If not EOF, continue to next pair
    }

    // There must be at least one pair
    ensuref(pairCount >= 1, "No input pairs found");

    // No extra tokens after last S
    inf.readEof();
}
