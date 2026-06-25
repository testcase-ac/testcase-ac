#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 10, "K");
    inf.readEoln();

    int n = 1;
    for (int i = 0; i < k; ++i) {
        n *= 4;
    }

    string s = inf.readToken("[JOI]+", "S");
    ensuref((int)s.size() == n, "S length must be 4^K: expected %d, got %d", n,
            (int)s.size());
    inf.readEoln();
    inf.readEof();
}
