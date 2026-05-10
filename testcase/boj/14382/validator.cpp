#include "testlib.h"
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // 2. Read N
        int N = inf.readInt(0, 1000000, "N");
        inf.readEoln();

        // 3. For each case, check that for N in [0, 10^6], the answer always exists or is INSOMNIA
        // The problem says: "If it's impossible, output INSOMNIA"
        // Let's check that for N=0, it's impossible (never reach all digits), for N>0, always possible

        if (N == 0) {
            // For N=0, only 0 is ever seen, never all digits
            continue;
        } else {
            // For N>0, simulate up to a reasonable bound to ensure all digits are eventually seen
            // We'll use a set to track digits
            set<int> digits_seen;
            // To avoid infinite loop, set a reasonable upper bound for iterations
            // Since N <= 1e6, and each time we get at least one new digit, at most 1000*10 iterations is more than enough
            for (long long mult = 1; mult <= 1000000; ++mult) {
                long long val = N * mult;
                long long tmp = val;
                if (tmp == 0) digits_seen.insert(0);
                while (tmp > 0) {
                    digits_seen.insert(tmp % 10);
                    tmp /= 10;
                }
                if ((int)digits_seen.size() == 10) break;
            }
            ensuref((int)digits_seen.size() == 10, "For N=%d, not all digits 0-9 can be seen within 1e6 multiples", N);
        }
    }

    inf.readEof();
}
