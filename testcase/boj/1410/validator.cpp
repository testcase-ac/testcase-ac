#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 15, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read N patterns, check constraints
    int pattern_length = -1;
    for (int i = 0; i < N; ++i) {
        string pat = inf.readLine("[a-z\\?]{1,50}", "pattern");
        if (pattern_length == -1) {
            pattern_length = (int)pat.length();
            // Upper bound already enforced by regex; keep a clear message just in case
            ensuref(pattern_length <= 50, "Pattern length must be at most 50, got %d", pattern_length);
        } else {
            ensuref((int)pat.length() == pattern_length,
                "All patterns must have the same length. Pattern %d has length %d, expected %d",
                i + 1, (int)pat.length(), pattern_length);
        }
    }

    inf.readEof();
}
