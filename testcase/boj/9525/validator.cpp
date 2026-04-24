#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board size
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N lines of the board
    for (int i = 1; i <= N; i++) {
        // Each line must consist only of '.' or 'X', length exactly N
        char buf[16];
        sprintf(buf, "row_%d", i);
        // Regex ensures only '.' or 'X' and length between 1 and 100
        string s = inf.readLine("[.X]{1,100}", buf);
        ensuref((int)s.size() == N,
                "%s: expected length %d but got %d", buf, N, (int)s.size());
        // (Regex already forbids other characters, so no extra per-char check needed)
    }

    inf.readEof();
    return 0;
}
