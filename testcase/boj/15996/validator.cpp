#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 2147483647, "N");
    inf.readSpace();
    int a = inf.readInt(2, 11, "A");
    inf.readEoln();

    const set<int> primes = {2, 3, 5, 7, 11};
    ensuref(primes.count(a) == 1, "A must be prime: %d", a);

    inf.readEof();
}
