#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a single token consisting only of 'Y' and 'N'
    string s = inf.readToken("[YN]+", "state");
    inf.readEoln();

    int n = (int)s.size();
    ensuref(1 <= n && n <= 1000, "Number of bulbs N must be in [1, 1000], but got %d", n);

    // No further constraints; the token already ensures only 'Y'/'N' characters.
    inf.readEof();
}
