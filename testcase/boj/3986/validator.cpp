#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Total length counter
    long long total_len = 0;

    // Read each word
    for (int i = 0; i < N; i++) {
        // Read a token consisting only of 'A' and 'B'
        string s = inf.readToken("[AB]+", "word");
        int len = s.length();
        inf.readEoln();

        // Check length constraints for each word
        ensuref(len >= 2 && len <= 100000,
                "Length of word %d is %d, but must be in [2, 100000]", i+1, len);

        total_len += len;
        // Check running total does not exceed 1e6
        ensuref(total_len <= 1000000LL,
                "Sum of word lengths exceeded 1e6 after reading word %d (total=%lld)",
                i+1, total_len);
    }

    // Ensure no extra content
    inf.readEof();
    return 0;
}
