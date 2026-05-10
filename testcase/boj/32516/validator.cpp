#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read T
    string T = inf.readToken("[a-z\\?]{1,200000}", "T");
    ensuref((int)T.size() == N, "Length of T (%d) does not match N (%d)", (int)T.size(), N);

    // Check all characters are lowercase or '?'
    for (int i = 0; i < N; ++i) {
        char c = T[i];
        ensuref((c >= 'a' && c <= 'z') || c == '?', "T[%d] = '%c' is not a lowercase letter nor '?'", i+1, c);
    }

    inf.readEoln();
    inf.readEof();
}
