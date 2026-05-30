#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 9, "N");
    inf.readEoln();

    // 2. Read 5 lines, each of length 4*N-1
    int expected_len = 4 * N - 1;
    for (int row = 0; row < 5; ++row) {
        string s = inf.readLine("[#\\.]{1,35}", "display row");
        ensuref((int)s.size() == expected_len,
                "Row %d: Expected length %d, got %d", row + 1, expected_len, (int)s.size());
        for (int i = 0; i < (int)s.size(); ++i) {
            ensuref(s[i] == '#' || s[i] == '.',
                    "Row %d, col %d: Invalid character '%c', only '#' and '.' allowed",
                    row + 1, i + 1, s[i]);
            if (i % 4 == 3) {
                ensuref(s[i] == '.',
                        "Row %d, separator col %d must be off", row + 1, i + 1);
            }
        }
    }

    inf.readEof();
}
