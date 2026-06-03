#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    string row1 = inf.readToken("[.#]{1,100000}", "S_1");
    inf.readEoln();
    string row2 = inf.readToken("[.#]{1,100000}", "S_2");
    inf.readEoln();

    ensuref((int)row1.size() == n, "S_1 length must be N: expected %d, got %d", n,
            (int)row1.size());
    ensuref((int)row2.size() == n, "S_2 length must be N: expected %d, got %d", n,
            (int)row2.size());

    inf.readEof();
}
