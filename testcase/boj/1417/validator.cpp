#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of candidates N: 1 ≤ N ≤ 50
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // For each candidate i = 1..N, read the number of people voting for them.
    // According to the statement, each vote count is a natural number ≤ 100.
    for (int i = 1; i <= N; i++) {
        inf.readInt(1, 100, "vote_" + to_string(i));
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
