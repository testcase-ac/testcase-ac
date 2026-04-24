#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read seat configuration string
    string s = inf.readToken("[SL]{1,50}", "s");
    // Must match exactly N seats
    ensuref((int)s.size() == N,
            "Length of seat string 's' is %d but expected %d", (int)s.size(), N);

    // Check that every maximal contiguous run of 'L' has even length (couples)
    for (int i = 0; i < N; ) {
        if (s[i] == 'L') {
            int j = i;
            while (j < N && s[j] == 'L') j++;
            int len = j - i;
            ensuref(len % 2 == 0,
                    "Contiguous run of L from position %d to %d has odd length %d",
                    i+1, j, len);
            i = j;
        } else {
            i++;
        }
    }
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
