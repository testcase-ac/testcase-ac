#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L
    int L = inf.readInt(6, 10000, "L");
    inf.readEoln();

    // Read R
    int R = inf.readInt(1, 99, "R");
    inf.readEoln();

    // Simulate the tree growth and sum the lengths of all branches (excluding the trunk)
    long long total = 0;
    long long prev_len = L;
    long long branches = 1; // Number of branches at current level (starts at 1 for trunk)
    int level = 0;

    while (true) {
        long long next_len = (prev_len * R) / 100;
        if (next_len <= 5) break;
        branches *= 2;
        total += branches * next_len;
        prev_len = next_len;
        level++;
        // Defensive: break if branches or total overflows (shouldn't happen for given constraints)
        ensuref(branches <= (1LL << 40), "Too many branches at level %d: %lld", level, branches);
        ensuref(total <= 2000000LL, "Total branch length overflow: %lld", total);
    }

    // The problem says: "총 길이의 합이 10^6보다 작거나 같은 입력만 주어진다."
    ensuref(total <= 1000000LL, "Total branch length exceeds 1,000,000: %lld", total);

    inf.readEof();
}
