#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);

    string cows = inf.readToken("[GH]{2,200000}", "cows");
    inf.readEoln();
    ensuref((int)cows.size() == n, "cows length must be N: expected %d, found %d", n, (int)cows.size());

    inf.readEof();
    return 0;
}
